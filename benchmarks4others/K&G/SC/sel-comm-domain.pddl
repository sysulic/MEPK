(define (domain dhmiourgimeno)
(:requirements :conditional-effects)
(:predicates
(phis0) 
(phis1) 
(p1as0) 
(p1as1) 
(p2as0) 
(p2as1) 
(p3as0) 
(p3as1) 
(p4as0) 
(p4as1) 
(p1bs0) 
(p1bs1) 
(p2bs0) 
(p2bs1) 
(p3bs0) 
(p3bs1) 
(p4bs0) 
(p4bs1) 
(p1cs0) 
(p1cs1) 
(p2cs0) 
(p2cs1) 
(p3cs0) 
(p3cs1) 
(p4cs0) 
(p4cs1) 
(auxs0) 
(auxs1) 
(p1a) 
(p2a) 
(p3a) 
(p4a) 
(goal0)
(goal1)
(goal2)
(goal3)
(goal4)
(goal5)
(goal6)
(goal7)
(kaphis0) 
(kaphis1) 
(kbphis0) 
(kbphis1) 
(kbnot_phis0) 
(kbnot_phis1) 
(kcphis0) 
(kcphis1) 
(kcnot_phis0) 
(kcnot_phis1) 
(s0s0a)
(s0s1a)
(s1s1a)
(s0s0b)
(s0s1b)
(s1s1b)
(s0s0c)
(s0s1c)
(s1s1c)
)
 (:action a_moves_left
:effect ( and 
( when (and (p2as0) ) (and (not(p2as0)) (p1as0) ))
( when (and (p2as1) ) (and (not(p2as1)) (p1as1) ))
( when (and (p3as0) ) (and (not(p3as0)) (p2as0) ))
( when (and (p3as1) ) (and (not(p3as1)) (p2as1) ))
( when (and (p4as0) ) (and (not(p4as0)) (p3as0) ))
( when (and (p4as1) ) (and (not(p4as1)) (p3as1) ))

))


 (:action a_senses_phi
:precondition (and  (p2a) )
:effect ( and 
( when (and (phis0) (not(phis1))) (and (s0s1a) ))
( when (and (phis1) (not(phis0))) (and (s0s1a) ))
 ))


 (:action all_sense_a
:precondition (and  (p1a) )
:effect ( and 
( when (and (kaphis0) (not(kaphis1))) (and (s0s1b) ))
( when (and (kaphis1) (not(kaphis0))) (and (s0s1b) ))
( when (and (auxs0) (not(auxs1))) (and (s0s1c) ))
( when (and (auxs1) (not(auxs0))) (and (s0s1c) ))
 ))


 (:action all_sense_a
:precondition (and  (p2a) )
:effect ( and 
( when (and (kaphis0) (not(kaphis1))) (and (s0s1b) ))
( when (and (kaphis1) (not(kaphis0))) (and (s0s1b) ))
( when (and (kaphis0) (not(kaphis1))) (and (s0s1c) ))
( when (and (kaphis1) (not(kaphis0))) (and (s0s1c) ))
 ))


 (:action all_sense_a
:precondition (and  (p3a) )
:effect ( and 
( when (and (kaphis0) (not(kaphis1))) (and (s0s1b) ))
( when (and (kaphis1) (not(kaphis0))) (and (s0s1b) ))
( when (and (kaphis0) (not(kaphis1))) (and (s0s1c) ))
( when (and (kaphis1) (not(kaphis0))) (and (s0s1c) ))
 ))


 (:action all_sense_a
:precondition (and  (p4a) )
:effect ( and 
( when (and (auxs0) (not(auxs1))) (and (s0s1b) ))
( when (and (auxs1) (not(auxs0))) (and (s0s1b) ))
( when (and (kaphis0) (not(kaphis1))) (and (s0s1c) ))
( when (and (kaphis1) (not(kaphis0))) (and (s0s1c) ))
 ))


 (:action a_moves_right
:effect ( and 
( when (and (p1as0) ) (and (not(p1as0)) (p2as0) ))
( when (and (p1as1) ) (and (not(p1as1)) (p2as1) ))
( when (and (p2as0) ) (and (not(p2as0)) (p3as0) ))
( when (and (p2as1) ) (and (not(p2as1)) (p3as1) ))
( when (and (p3as0) ) (and (not(p3as0)) (p4as0) ))
( when (and (p3as1) ) (and (not(p3as1)) (p4as1) ))

))


(:derived (p1a) 
(and
(or (p1as0) (s0s0a))
(or (p1as1) (s1s1a))
))
(:derived (p2a) 
(and
(or (p2as0) (s0s0a))
(or (p2as1) (s1s1a))
))
(:derived (p3a) 
(and
(or (p3as0) (s0s0a))
(or (p3as1) (s1s1a))
))
(:derived (p4a) 
(and
(or (p4as0) (s0s0a))
(or (p4as1) (s1s1a))
))

(:derived (goal0)
(or (not(kbphis0)) (s0s0a) ))
(:derived (goal1)
(or (not(kbphis1)) (s1s1a) ))
(:derived (goal2)
(or (not(kbnot_phis0)) (s0s0a) ))
(:derived (goal3)
(or (not(kbnot_phis1)) (s1s1a) ))
(:derived (goal4)
(or (p1as0) (s0s0a) ))
(:derived (goal5)
(or (p1as1) (s1s1a) ))
(:derived (goal6)
(or (kcphis0) (kcnot_phis0) (s0s0a) ))
(:derived (goal7)
(or (kcphis1) (kcnot_phis1) (s1s1a) ))
(:derived (kaphis0) 
(and
(phis0)
(or (phis1) (s0s1a) ) 
))

(:derived (kaphis1) 
(and
(phis1)
(or (phis0) (s0s1a) ) 
))

(:derived (kbphis0) 
(and
(phis0)
(or (phis1) (s0s1b) ) 
))

(:derived (kbphis1) 
(and
(phis1)
(or (phis0) (s0s1b) ) 
))

(:derived (kbnot_phis0) 
(and
(not(phis0))
(or (not(phis1)) (s0s1b) ) 
))

(:derived (kbnot_phis1) 
(and
(not(phis1))
(or (not(phis0)) (s0s1b) ) 
))

(:derived (kcphis0) 
(and
(phis0)
(or (phis1) (s0s1c) ) 
))

(:derived (kcphis1) 
(and
(phis1)
(or (phis0) (s0s1c) ) 
))

(:derived (kcnot_phis0) 
(and
(not(phis0))
(or (not(phis1)) (s0s1c) ) 
))

(:derived (kcnot_phis1) 
(and
(not(phis1))
(or (not(phis0)) (s0s1c) ) 
))

)
