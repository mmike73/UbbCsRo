(defun sub_stang (arb nv nm)
    (cond
        ((null arb) nil)
        ((= nv (+ nm 1)) nil)
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
        (t (sub_drept (cddr arb) (+ 1 nv) (+ (cadr arb) nm)))
    )
)

(defun apartine (e arb)
    (cond
        ((null arb) nil)
        ((equal e (car arb)) t)
        (t (apartine e (cdr arb)))
    )
)

(defun adancime_nod (e arb dpt)
    (cond
        ((null arb) nil)
        ((equal e (car arb)) dpt)
        ((apartine e (sub_stang (cddr arb) 0 0)) (adancime_nod e (sub_stang (cddr arb) 0 0) (+ 1 dpt)))
        ((apartine e (sub_drept (cddr arb) 0 0)) (adancime_nod e (sub_drept (cddr arb) 0 0) (+ 1 dpt)))
        (t nil)
    )
)