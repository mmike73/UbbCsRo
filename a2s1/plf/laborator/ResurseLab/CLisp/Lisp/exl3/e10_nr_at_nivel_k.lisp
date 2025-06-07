(defun nr_at_k (arb k crt)
    (cond
        ((null arb) 0)
        ((and (atom arb) (= crt k)) 1)
        ((atom arb) 0)
        (t (apply #'+ (mapcar #'(lambda (arb) (nr_at_k arb k (+ crt 1))) arb)))
    )
)

;(a (b (d (e (f)))) (c (g (h (i (j (k (l)))))))
;(d (e (f)))) (g (h (i (j (k (l)))))))
;        a
;   b         c
;d              g
; e             h
;f             i
;             j
;              k
;             l


;(a (b (f)) (c (g (h)) (i)) (d (e)))
;                a
;      b        c       d
;   f          g  i      e
;             h