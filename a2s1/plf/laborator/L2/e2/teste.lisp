(defun test_noduri_nivel_k ()
    (equal (noduri_nivel_k '(a 2 b 2 r 2 t 0 w 0 s 0 c 2 d 0 e 0) 0) '(A))
    (equal (noduri_nivel_k '(a 2 b 2 r 2 t 0 w 0 s 0 c 2 d 0 e 0) 1) '(B C))
    (equal (noduri_nivel_k '(a 2 b 2 r 2 t 0 w 0 s 0 c 2 d 0 e 0) 2) '(R S D E))
    (equal (noduri_nivel_k '(a 2 b 2 r 2 t 0 w 0 s 0 c 2 d 0 e 0) 3) '(T W))
    
    (equal (noduri_nivel_k '(a 1 b 1 r 1 t 1 w 1 s 1 c 1 d 1 e 0) 0) '(A))
    (equal (noduri_nivel_k '(a 1 b 1 r 1 t 1 w 1 s 1 c 1 d 1 e 0) 1) '(B))
    (equal (noduri_nivel_k '(a 1 b 1 r 1 t 1 w 1 s 1 c 1 d 1 e 0) 2) '(R))
    (equal (noduri_nivel_k '(a 1 b 1 r 1 t 1 w 1 s 1 c 1 d 1 e 0) 3) '(T))
    (equal (noduri_nivel_k '(a 1 b 1 r 1 t 1 w 1 s 1 c 1 d 1 e 0) 4) '(W))
    (equal (noduri_nivel_k '(a 1 b 1 r 1 t 1 w 1 s 1 c 1 d 1 e 0) 5) '(S))
    (equal (noduri_nivel_k '(a 1 b 1 r 1 t 1 w 1 s 1 c 1 d 1 e 0) 6) '(C))
    (equal (noduri_nivel_k '(a 1 b 1 r 1 t 1 w 1 s 1 c 1 d 1 e 0) 7) '(D))
    (equal (noduri_nivel_k '(a 1 b 1 r 1 t 1 w 1 s 1 c 1 d 1 e 0) 8) '(E))

    (equal (noduri_nivel_k '(a 2 b 0 r 1 t 1 w 1 s 1 c 1 d 1 e 0) 0) '(A))
    (equal (noduri_nivel_k '(a 2 b 0 r 1 t 1 w 1 s 1 c 1 d 1 e 0) 1) '(B R))

    (equal (noduri_nivel_k '(a 2 b 1 h 1 i 1 j 0 c 2 d 2 f 1 k 0 g 0 e 0) 0) '(A))
    (equal (noduri_nivel_k '(a 2 b 1 h 1 i 1 j 0 c 2 d 2 f 1 k 0 g 0 e 0) 1) '(B C))
    (equal (noduri_nivel_k '(a 2 b 1 h 1 i 1 j 0 c 2 d 2 f 1 k 0 g 0 e 0) 2) '(H D E))
    (equal (noduri_nivel_k '(a 2 b 1 h 1 i 1 j 0 c 2 d 2 f 1 k 0 g 0 e 0) 3) '(I F G))
    (equal (noduri_nivel_k '(a 2 b 1 h 1 i 1 j 0 c 2 d 2 f 1 k 0 g 0 e 0) 4) '(J K))
    (equal (noduri_nivel_k '(a 2 b 1 h 1 i 1 j 0 c 2 d 2 f 1 k 0 g 0 e 0) 5) '())
  ;;;      A
  ;;;  B       C
  ;;; H      D   E
  ;;;  I   F   G
  ;;; J   K
)