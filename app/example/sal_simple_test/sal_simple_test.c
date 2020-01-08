/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */
#include <stdio.h>
#include <string.h>

#include "aos/cli.h"
#include "aos/kernel.h"
#include "aos/yloop.h"
#include "ulog/ulog.h"
#include "aos/hal/uart.h"
#include <network/network.h>
#include <netmgr.h>
#include <k_api.h>
#include <atcmd_config_module.h>

#define TAG "sal_demo"
#define TCP_SEND_MAX_LEN 16

/* Change below 2 lines to you own TCP echo server. */
#define TCP_ECHO_SERVER "47.111.5.71"
#define TCP_ECHO_SERVER_PORT 30001

static void sal_tcp_test()
{
    int  ret = 0;
    int  readlen = 0;
    int  fd = 0;
    int  time = 0;
    long long end_time = 0;
    int  testtimes = 1;
    int  total_len;
    char *pcipaddr = NULL;
    short pcdestport;
    char *pcdata = NULL;
    int pctesttime;
    struct sockaddr_in addr;
    struct timeval timeout;
    unsigned int seed = (unsigned int)aos_now();
    int to_send_len;
    static char send_buffer[TCP_SEND_MAX_LEN], read_buffer[TCP_SEND_MAX_LEN];

    pcipaddr = TCP_ECHO_SERVER;
    pcdestport = TCP_ECHO_SERVER_PORT;
    pctesttime = 30; /* 30s */
    end_time = pctesttime * 1000 + aos_now_ms();

    memset(&addr, 0, sizeof(addr));
    addr.sin_port = htons(pcdestport);
    addr.sin_addr.s_addr = inet_addr(pcipaddr);
    addr.sin_family = AF_INET;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0){
        LOG("fail to creat socket errno = %d \r\n", errno);
        return -1;
    }

    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
        LOG("Connect failed, errno = %d, ip %s port %d \r\n",
            errno, pcipaddr, pcdestport);
        goto err;
    }

    srand(seed);
    while (1) {
        /* construct to-send content */
        int l;
        to_send_len = rand() % sizeof(send_buffer) - 1;
        if (to_send_len < 1) to_send_len = 1;

        memset(send_buffer, 0, sizeof(send_buffer));
        for (l = 0; l < to_send_len; l++) {
            send_buffer[l] = rand() % ('z' - 'a') + 'a';
        }

        /* send-recv */
        LOG("Sending %s\r\n ...", send_buffer);
        if ((ret = send(fd, send_buffer, strlen(send_buffer), 0)) <= 0) {
            LOG("send data failed, errno = %d. for the %d time \r\n", errno, time);
            goto err;
        }

        total_len = 0;
        memset(read_buffer, 0, sizeof(read_buffer));
        do {
            readlen = read(fd, read_buffer + total_len, to_send_len - total_len);
            if (readlen < 0 && errno != EINTR && errno != EWOULDBLOCK
                && errno != EALREADY && errno != EINPROGRESS){
                LOG("recv failed, errno = %d.\r\n", errno);
                goto err;
            }

            if (readlen == 0){
                LOG("socket is closed\r\n");
                break;
            }
            total_len += readlen;
        } while (total_len < to_send_len);

        LOG("Received: %s\r\n", read_buffer);

        if (strncmp(send_buffer, read_buffer, to_send_len) != 0) {
            LOG("Unexpected content recevied at the %-th round test.\r\n", time);
            LOG("  Sent: %s\r\n", send_buffer);
            LOG("  Recv: %s\r\n", read_buffer);
            goto err;
        }

        LOG("The %d-th round test finished\r\n", time);

        time++;

        if (end_time < aos_now_ms()){
            break;
        }
    }

    close(fd);
    LOGD(TAG, "SAL TCP demo end");
    return 0;

err:
    close(fd);
    LOGD(TAG, "SAL TCP demo end with failure");
    return -1;
}

/* UDP payload for testing, binary data. */
static const char *udp_payload = "\x40\x01\x73\x6a\x37\x63\x6f\x61\x70\x2e\x6d\x65";

static void sal_udp_test()
{
    int ret, fd;
    const char *server_ipaddr = "134.102.218.18";
    const short server_port = 5683;
    struct sockaddr_in addr;

    LOGD(TAG, "SAL UDP demo start");

    memset(&addr, 0, sizeof(addr));
    addr.sin_port = htons(server_port);
    addr.sin_addr.s_addr = inet_addr(server_ipaddr);
    addr.sin_family = AF_INET;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0){
        LOGE(TAG, "Failed to create socket, errno = %d", errno);
        return;
    } else {
        LOGD(TAG, "UDP socket create OK");
    }

    ret = sendto(fd, udp_payload, strlen(udp_payload), 0, (struct sockaddr*)&addr, sizeof(addr));
    if (ret < 0){
        LOGE(TAG, "udp sendto failed, errno = %d", errno);
        close(fd);
        return;
    } else {
        LOGD(TAG, "UDP socket sendto OK");
    }

    close(fd);

    LOGD(TAG, "SAL UDP demo end");
}

static void sal_test()
{
    LOGD(TAG, "SAL test start");
    sal_tcp_test();
    sal_udp_test();
    LOGD(TAG, "SAL test end");
}

static void wifi_event_handler(input_event_t *event, void *priv_data)
{
    if (event->type != EV_WIFI) return;

    if (event->code == CODE_WIFI_ON_PRE_GOT_IP)
        LOG("Hello, WiFi PRE_GOT_IP event!");

    if (event->code == CODE_WIFI_ON_GOT_IP){
        LOG("Hello, WiFi GOT_IP event!");
        /* Only start to connect socket after network is ready. */
        aos_msleep(2000);
        sal_test();
    }
}

#ifdef CONFIG_PRINT_HEAP
void print_heap()
{
    extern k_mm_head *g_kmm_head;
    int               free = g_kmm_head->free_size;
    LOG("============free heap size =%d==========", free);
}
#endif

static void _delayed_action(void *arg)
{
#ifdef CONFIG_PRINT_HEAP
    print_heap();
#endif
    aos_post_delayed_action(2000, _delayed_action, NULL);
}

/**
 * Application entry.
 */
int application_start(int argc, char *argv[])
{
    sal_device_config_t data = {0};

    /**
     * uart port number:
     *    - 1
     * @note subject to change according to your case.
     *
     * module uart config:
     *    - 9600
     *    - 8n1
     *    - no flow control
     *    - tx/rx mode
     *
     * @note These configs are subject to change according to the module you use.
     */
    data.uart_dev.port = 1;
    data.uart_dev.config.baud_rate = 9600;
    data.uart_dev.config.data_width = DATA_WIDTH_8BIT;
    data.uart_dev.config.parity = NO_PARITY;
    data.uart_dev.config.stop_bits  = STOP_BITS_1;
    data.uart_dev.config.flow_control = FLOW_CONTROL_DISABLED;
    data.uart_dev.config.mode = MODE_TX_RX;

    aos_set_log_level(AOS_LL_DEBUG);

    /**
     * Register and Initialize SAL device.
     *
     * Attention:
     *     (1) If register SAL device using "sal_add_dev(NULL, NULL)",
     *         it means to use the device and related configuration
     *         prodived in board settings (e.g. module ?= wifi.bk7231 
     *         in board/developer/aos.mk).
     *     (2) If want to register SAL device with specific parameters,
     *         Please use 'sal_add_dev("<device_name>", "<dev_para>")',
     *         in which the <device_name> is the module name of the AT device,
     *         and fill in the <dev_para> with UART config parameters.
     */
    if (sal_add_dev("m5310a", &data) != 0) {
        LOG("Failed to add SAL device!");
        return -1;
    }

    /* Initialize the SAL core. */
    sal_init();

    /**
     * Register WiFi event handler, SAL device will post the GOT_IP
     * event once the network is connected, only after the event socket
     * code can be executed.
     */
    aos_register_event_filter(EV_WIFI, wifi_event_handler, NULL);

    aos_post_delayed_action(2000, _delayed_action, NULL);

    /* Enter into aos yloop scheduler, will not return. */
    aos_loop_run();

    return 0;
}
