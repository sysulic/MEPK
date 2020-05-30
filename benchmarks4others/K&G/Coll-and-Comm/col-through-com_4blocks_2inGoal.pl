%%
%%
%%	Collaboration through Communication Example
%%
%%      - 2 agents, 4 rooms, 4 blocks 
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
p_commonknowledge([

    ]).
n_commonknowledge([

    ]).

user_input_states([
    ]).

goal([

	or([k(a,r1red),k(a,r3red),k(a,r4red)]), 
	or([k(b,r1blue),k(b,r3blue),k(b,r4blue)])
	]).

static_atoms([r1blue,r2blue,r3blue,r4blue,
      r1red,r2red,r3red,r4red,
      r1pink,r3pink,r4pink,
      r1green,r3green,r4green]).

num_events(1).
num_agents(2).
agents([a,b]).		
atoms([
    r1a,r2a,r3a,r4a,
	  r1b,r2b,r3b,r4b,

     r1blue,r2blue,r3blue,r4blue,
	  r1red,r2red,r3red,r4red,
	  r1pink,r2pink,r3pink,r4pink,
	  r1green,r2green,r3green,r4green
	 
   ]).

p_commonknowledge([r2a,r2b]).
n_commonknowledge([r2red, r2blue,r2green,r2pink,r1a,r3a,r4a,r1b,r3b,r4b]).


possibleactions([  
  

            [b_moves_left,or([neg(g),g]),action([[r2b],[r3b],[r4b]], [[r2b],[r3b],[r4b]], [[r1b],[r2b],[r3b]])],
            [b_moves_right,or([neg(g),g]),action([[r1b],[r2b],[r3b]], [[r1b],[r2b],[r3b]], [[r2b],[r3b],[r4b]])],
                       
            [b_senses_in_r1,[r1b],sense([b],[[r1red, r1blue, r1pink,r1green]])],
            [b_senses_in_r1,[r2b],sense([b],[[r2red, r2blue, r2pink,r2green]])],
            [b_senses_in_r3,[r3b],sense([b],[[r3red, r3blue, r3pink,r3green]])],
            [b_senses_in_r4,[r4b],sense([b],[[r4red, r4blue, r4pink,r4green]])],
           
             [b_senses_if_a_knows_blue_in_r3,or([neg(g),g]),sense([b],[[k(a,r3blue)]])], 
             [b_senses_if_a_knows_blue_in_r2,or([neg(g),g]),sense([b],[[k(a,r2blue)]])], 
             [b_senses_if_a_knows_blue_in_r4,or([neg(g),g]),sense([b],[[k(a,r4blue)]])], 
             [b_senses_if_a_knows_blue_in_r1,or([neg(g),g]),sense([b],[[k(a,r1blue)]])],

             [b_senses_if_a_knows_green_in_r3,or([neg(g),g]),sense([b],[[k(a,r3green)]])], 
             [b_senses_if_a_knows_green_in_r4,or([neg(g),g]),sense([b],[[k(a,r4green)]])], 
             [b_senses_if_a_knows_green_in_r1,or([neg(g),g]),sense([b],[[k(a,r1green)]])],
             [b_senses_if_a_knows_green_in_r2,or([neg(g),g]),sense([b],[[k(a,r2green)]])],

             [b_senses_if_a_knows_pink_in_r3,or([neg(g),g]),sense([b],[[k(a,r3pink)]])], 
             [b_senses_if_a_knows_pink_in_r4,or([neg(g),g]),sense([b],[[k(a,r4pink)]])], 
             [b_senses_if_a_knows_pink_in_r1,or([neg(g),g]),sense([b],[[k(a,r1pink)]])],   
             [b_senses_if_a_knows_pink_in_r2,or([neg(g),g]),sense([b],[[k(a,r2pink)]])],   

             [b_senses_if_a_knows_red_in_r2,or([neg(g),g]),sense([b],[[k(a,r2red)]])], 
             [b_senses_if_a_knows_red_in_r3,or([neg(g),g]),sense([b],[[k(a,r3red)]])], 
             [b_senses_if_a_knows_red_in_r4,or([neg(g),g]),sense([b],[[k(a,r4red)]])], 
             [b_senses_if_a_knows_red_in_r1,or([neg(g),g]),sense([b],[[k(a,r1red)]])],  

            [a_moves_left,or([neg(g),g]),action([[r2a],[r3a],[r4a]], [[r2a],[r3a],[r4a]], [[r1a],[r2a],[r3a]])],
            [a_moves_right,or([neg(g),g]),action([[r1a],[r2a],[r3a]], [[r1a],[r2a],[r3a]], [[r2a],[r3a],[r4a]])], 
            
            [a_senses_in_r1,r1a,sense([a],[[r1red, r1blue, r1pink,r1green]])],
            [a_senses_in_r2,r2a,sense([a],[[r2red, r2blue, r2pink,r2green]])],
            [a_senses_in_r3,r3a,sense([a],[[r3red, r3blue, r3pink,r3green]])],
            [a_senses_in_r4,r4a,sense([a],[[r4red, r4blue, r4pink,r4green]])],

            [a_senses_if_b_knows_red_in_r3,or([neg(g),g]),sense([a],[[k(b,r3red)]])], 
            [a_senses_if_b_knows_red_in_r2,or([neg(g),g]),sense([a],[[k(b,r2red)]])],
            [a_senses_if_b_knows_red_in_r1,or([neg(g),g]),sense([a],[[k(b,r1red)]])] , 
            [a_senses_if_b_knows_red_in_r4,or([neg(g),g]),sense([a],[[k(b,r4red)]])],

            [a_senses_if_b_knows_green_inr3,or([neg(g),g]),sense([a],[[k(b,r3green)]])], 
            [a_senses_if_b_knows_green_inr2,or([neg(g),g]),sense([a],[[k(b,r2green)]])], 
             [a_senses_if_b_knows_green_inr1,or([neg(g),g]),sense([a],[[k(b,r1green)]])] , 
             [a_senses_if_b_knows_green_inr4,or([neg(g),g]),sense([a],[[k(b,r4green)]])],

            [a_senses_if_b_knows_pink_inr3,or([neg(g),g]),sense([a],[[k(b,r3pink)]])], 
                        [a_senses_if_b_knows_pink_inr2,or([neg(g),g]),sense([a],[[k(b,r2pink)]])],  
 
             [a_senses_if_b_knows_pink_inr1,or([neg(g),g]),sense([a],[[k(b,r1pink)]])] , 
             [a_senses_if_b_knows_pink_inr4,or([neg(g),g]),sense([a],[[k(b,r4pink)]])],

            [a_senses_if_b_knows_blue_inr3,or([neg(g),g]),sense([a],[[k(b,r3blue)]])]  ,
                        [a_senses_if_b_knows_blue_inr2,or([neg(g),g]),sense([a],[[k(b,r2blue)]])]  ,

             [a_senses_if_b_knows_blue_inr1,or([neg(g),g]),sense([a],[[k(b,r1blue)]])] , 
             [a_senses_if_b_knows_blue_inr4,or([neg(g),g]),sense([a],[[k(b,r4blue)]])]       	

          	]).

run:-
	!,true.	

constraint(H):-

	cformula(r2a,H),
	cformula(r2b,H),
	cformula(or([r1blue,r3blue,r4blue]),H),
	cformula(or([r1red,r3red,r4red]),H),
	cformula(or([r1green,r3green,r4green]),H),
	cformula(or([r1pink,r3pink,r4pink]),H),
    \+  cformula(r2red,H),
    \+  cformula(r2blue,H),
    \+  cformula(r2green,H),
    \+  cformula(r2pink,H),

\+	cformula(r3a,H),
\+	cformula(r3b,H),
\+	cformula(r1a,H),
\+	cformula(r1b,H),
\+	cformula(r4a,H),
\+	cformula(r4b,H),
\+ 	cformula(and([r1blue,r3blue]),H),
\+ 	cformula(and([r1blue,r4blue]),H),
\+ 	cformula(and([r4blue,r3blue]),H),
\+ 	cformula(and([r1red,r3red]),H),
\+ 	cformula(and([r1red,r4red]),H),
\+ 	cformula(and([r4red,r3red]),H),
\+ 	cformula(and([r1green,r3green]),H),
\+ 	cformula(and([r1green,r4green]),H),
\+ 	cformula(and([r4green,r3green]),H),
\+ 	cformula(and([r1pink,r3pink]),H),
\+ 	cformula(and([r1pink,r4pink]),H),
\+ 	cformula(and([r4pink,r3pink]),H).


invariant([
  [r1a,r2a,r3a,r4a],
  [r1b,r2b,r3b,r4b]



  ]).
