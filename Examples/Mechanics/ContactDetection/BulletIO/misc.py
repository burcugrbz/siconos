#!/usr/bin/env python

#
# Multiples contactors with multiples non smooth laws
#


from Siconos.Mechanics.ContactDetection import Contactor
from Siconos.Mechanics.ContactDetection.Bullet import IO

# Creation of the hdf5 file for input/output
with IO.Hdf5(mode='w') as io:

    # Definition of two boxes shape
    io.insertPrimitiveShape('BigBox', 'Box', (3, 5, 2))

    io.insertPrimitiveShape('LongBox', 'Box', (1, 1, 5))

    # Definition of the ground shape
    io.insertPrimitiveShape('Ground', 'Box', (100, 100, .5))

    # Definition of a non smooth law between groups 0 and 1
    io.insertNewtonImpactFrictionNSL('contact1', mu=0.1,
                                     collision_group1=0, collision_group2=1)

    # Definition of a non smooth law between groups 1 and 1
    io.insertNewtonImpactFrictionNSL('contact2', mu=0.7,
                                     collision_group1=1, collision_group2=1)

    # Definition of a non smooth law between groups 0 and 0
    io.insertNewtonImpactFrictionNSL('contact3', mu=0.1,
                                     collision_group1=0, collision_group2=0)

    # A 'two boxes object made with two Contactors.
    # As a mass is given, it is a dynamic system involved in contact
    # detection and in the simulation.  
    io.insertObject('twoboxes', [Contactor('BigBox', 
                                           collision_group=0,
                                           relative_position=[0, 0, 0]),
                                 Contactor('LongBox', collision_group=1,
                                           relative_position=[0, 0, 0])],
                    position=[0, 0, 3],
                    velocity=[100, 0, 0, 10, 10, 10],
                    mass=.1)

    # the ground object made with the ground shape. As the mass is
    # not given, it is a static object only involved for contact
    # detection.
    io.insertObject('ground', [Contactor('Ground', collision_group=1)],
                    position=[0, 0, 0])


# Run the simulation from the inputs previously defined and add
# results to the hdf5 file. The visualisation of the output may be done
# with the vview command.
with IO.Hdf5(mode='r+') as io:

    io.run()
