src =Split(''' 
    sal_simple_test.c
''')
component =aos_component('sal_simple_test', src)

dependencis =Split(''' 
    kernel/yloop
    kernel/cli
    network/netmgr
    network/nal/sal
''')
for i in dependencis:
    component.add_comp_deps(i)





