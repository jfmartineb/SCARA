# Creando el Robot Harware Interface

1. Para empezar vamos a crear un paquete utilizando el siguiente código:

    ```sh
    catkin_create_pkg servo_control controller_manager roscpp rospy std_msgs std_srvs message_generation message_runtime
    ```

    `servo_control` es el nombre de nuestro paquete.

2. Modificamos el archivo `CMakeLists.txt` del paquete. 

    - Borramos del `find_package` el `message_runtime`
    - En `catkin_package` descomentamos el `INCLUDE_DIRS` y el `CATKIN_DEPENDS`, de este último borramos el `message generation`.
    - En `include_directories` descomentamos el `include`. 
    - Al final de la sección de build, agregamos las siguientes lineas : 
    
        ```CMake
        add_executable(servo_control_node src/servo_control_node.cpp)
        target_link_libraries(servo_control_node ${catkin_LIBRARIES})
        ```
    `servo_control_node` es el nombre que le asignaremos al nodo creado con C++.

