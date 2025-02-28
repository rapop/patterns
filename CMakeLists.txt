project(patters)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(abstract_factory abstract_factory.cpp)
add_executable(builder builder.cpp)
add_executable(factory_method factory_method.cpp)
add_executable(prototype prototype.cpp)
add_executable(singleton singleton.cpp)
add_executable(adapter adapter.cpp)
add_executable(bridge bridge.cpp)
add_executable(composite composite.cpp)
add_executable(decorator decorator.cpp)
add_executable(facade facade.cpp)
add_executable(flyweight flyweight.cpp)
add_executable(proxy proxy.cpp)
add_executable(chain_of_responsability chain_of_responsability.cpp)
add_executable(command command.cpp)
add_executable(interpreter interpreter.cpp)
add_executable(iterator iterator.cpp)
add_executable(mediator mediator.cpp)
add_executable(momento momento.cpp)
add_executable(observer observer.cpp)
add_executable(state state.cpp)
add_executable(strategy strategy.cpp)
add_executable(template_method template_method.cpp)
add_executable(visitor visitor.cpp)
add_executable(visitor_modern visitor_modern.cpp)

#pimpl
add_executable(pimpl_main pimpl_main.cpp pimpl.cpp)

#solid
add_executable(single_responsability_principle single_responsability_principle.cpp)
add_executable(open_closed_principle open_closed_principle.cpp)
add_executable(liskov_substitution_principle liskov_substitution_principle.cpp)
add_executable(interface_segregation_principle interface_segregation_principle.cpp)
add_executable(dependency_inversion_principle dependency_inversion_principle.cpp)