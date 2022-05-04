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

## Modificar

URDF del moveit : [Agregar el Namespace](https://answers.ros.org/question/214712/gazebo-controller-spawner-warning/)

```xml
    <gazebo>
        <plugin name="gazebo_ros_control" filename="libgazebo_ros_control.so">
            <robotNamespace>/scara</robotNamespace>
        </plugin>
    </gazebo>
```

## Tene cuidado 

- Nombres de los "types" de controladores. 