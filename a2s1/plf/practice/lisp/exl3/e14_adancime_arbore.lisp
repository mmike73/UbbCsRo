(defun adancime_arb (arb)
    (cond
        ((null (cdr arb)) 0)
        (t (+ 1 (apply #'max (mapcar #'adancime_arb (cdr arb)))))
    )
)

;(a (b (d (e (f)))) (c (g (h (i (j (k (l)))))))))

;               a
;           b       c
;         d   e    g h
;            f