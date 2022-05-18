Archivos correspondientes al semillero de investigació Ares de la Universidad EAFIT
Proyecto SCARA

## Instalar 

sudo apt-get install \
    ros-melodic-moveit \
    ros-melodic-controller-manager \
    ros-melodic-ros-control \
    ros-melodic-ros-controllers \ 
    ros-melodic-gazebo-ros-control

sudo apt-get install ros-melodic-ros-control ros-melodic-joint-state-controller ros-melodic-effort-controllers ros-melodic-position-controllers ros-melodic-velocity-controllers ros-melodic-ros-controllers ros-melodic-gazebo-ros ros-melodic-gazebo-ros-control

## A modificar en el package de moveit

Hay 4 archivos que deben ser modificados:

1. `@_moveit_controller_manager.launch.xml`:

    Cambiar el archivo de configuración de los controladores.

2. `ros_controllers.launch`:

    Cambiar el archivo de configuración de los controladores.
    En el nodo "controller_spawner" agregar en namespace ("ns") y los argumentos ("args") de los controladores a crear.

3. `demo_gazebo.launch`:

    En el nodo "joint_state_publisher" agregamos al parámetro "source_list" el namespace.

4.  `sensor_3d.yaml`:

    Borrar todas las lineas y poner esto `sensors: []`

5. Adicionalmente en el urdf que saca MoveIt le ponemos el namespace al robot.

    URDF del moveit : [Agregar el Namespace](https://answers.ros.org/question/214712/gazebo-controller-spawner-warning/)

    ```xml
        <gazebo>
            <plugin name="gazebo_ros_control" filename="libgazebo_ros_control.so">
                <robotNamespace>/scara</robotNamespace>
            </plugin>
        </gazebo>
    ```


## Tener cuidado 

- Nombres de los "types" de controladores. 

## Troubleshooting 

- **Cuando la simulación en Gazebo colapsa** cambiar [las ganancias de los controladores](https://answers.ros.org/question/216092/problem-with-the-robot-model-collapsing/).

# Trabajos futuros

- [Labrador Aya, J.I. (2020).Simulación de un robot hexapodo con ros y gazebo](http://hdl.handle.net/20.500.12010/16932)
- [Igual Bañó, C. (2014). Diseño, monitorización y control de un hexápodo con ROS](http://hdl.handle.net/10251/49831)