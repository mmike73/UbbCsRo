(defun sub_stang (arb nv nm)
    (cond
        ((null arb) nil)
        ((= nv (+ 1 nm)) nil)
        (t (cons
                (car arb)
                (cons
                    (cadr arb)
                    (sub_stang (cddr arb) (+ 1 nv) (+ (cadr arb) nm))
                )
           )
        )
    )
)

(defun sub_drept (arb nv nm)
    (cond
        ((null arb) nil)
        ((= nv (+ nm 1)) arb)
        (t (sub_drept (cddr arb) (+ nv 1) (+ nm (cadr arb))))
    )
)   

(defun nr_niveluri (arb)
    (cond
        ((null arb) 0)
        (t (max (+ 1 (nr_niveluri (sub_stang (cddr arb) 0 0))) (+ 1 (nr_niveluri (sub_drept (cddr arb) 0 0)))))
    )
)