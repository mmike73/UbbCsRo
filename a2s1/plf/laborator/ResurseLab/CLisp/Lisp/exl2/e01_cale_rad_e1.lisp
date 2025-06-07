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
        ((= nv (+ 1 nm)) arb)
        (t (sub_drept (cddr arb) (+ 1 nv) (+ (cadr arb) nm)))
    )
)

(defun apartine (e arb)
    (cond
        ((null arb) nil)
        ((equal (car arb) e) t)
        (t (apartine e (cddr arb)))
    )
)

(defun cale_rad_e (arb e Col)
    (cond
        ((null arb) Col)
        ((equal e (car arb)) (append Col (list (car arb))))
        ((apartine e (sub_stang (cddr arb) 0 0)) 
            (cale_rad_e (sub_stang (cddr arb) 0 0) e (append Col (list(car arb)))))
        ((apartine e (sub_drept (cddr arb) 0 0)) 
            (cale_rad_e (sub_drept (cddr arb) 0 0) e (append Col (list (car arb)))))
        (t nil)
    )
)

;(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 0 h 0)
           
           ;a
        ;b      d
    ;c    f   e   h
;i       g