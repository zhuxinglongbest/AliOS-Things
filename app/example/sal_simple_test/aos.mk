NAME := sal_simple_test

$(NAME)_MBINS_TYPE := app
$(NAME)_VERSION := 1.0.0
$(NAME)_SUMMARY :=
$(NAME)_SOURCES := sal_simple_test.c

$(NAME)_COMPONENTS := yloop sal

$(NAME)_INCLUDES += ./

GLOBAL_DEFINES += CONFIG_PRINT_HEAP
