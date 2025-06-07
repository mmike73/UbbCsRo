(defun parcurgere_stang (arb nv nm)
    (cond
        ((null arb) nil)
        ((= nv (+ 1 nm)) nil)
        (t (cons (car arb)
                (cons (cadr arb)
                    (parcurgere_stang (cddr arb) (+ 1 nv) (+ (cadr arb) nm))
                )
            )
        )
    )
)

(defun parcurge_drept (arb nv nm)
    (cond
        ((null arb) nil)
        ((= nv (+ 1 nm)) arb)
        (t (parcurge_drept (cddr arb) (+ 1 nv) (+ (cadr arb) nm)))
    )
)

(defun get_subarbore_stang_drept (arb)
    (append
        (list (parcurgere_stang (cddr arb) 0 0))
        (list (parcurge_drept (cddr arb) 0 0))
    )
)

(defun inordine (arb)
    (cond
        ((null arb) nil)
        (t (append
                (inordine (parcurgere_stang (cddr arb) 0 0)) 
                (list (car arb))                            
                (inordine (parcurge_drept (cddr arb) 0 0))
        )
        )
    )
)

(defun noduri_nivel_k_helper (arb k current-depth)
    (cond
        ((null arb) nil)
        ((= current-depth k) (list (car arb)))
        (t (append
            (noduri_nivel_k_helper (parcurgere_stang (cddr arb) 0 0) k (+ current-depth 1))
            (noduri_nivel_k_helper (parcurge_drept (cddr arb) 0 0) k (+ current-depth 1))
            )
        )
    )
)

(defun noduri_nivel_k (arb k)
    (noduri_nivel_k_helper arb k 0)
)



"      a
   b     c
 r   s d   e  
t w"
;;;(noduri_nivel_k '(a 2 b 2 r 2 t 0 w 0 s 0 c 2 d 0 e 0) 3)