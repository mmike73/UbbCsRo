(defun nr_noduri (l)
    (cond
        ((null (cdr l)) 1)
        (t (+ 1 (apply #'+ (mapcar #'nr_noduri (cdr l)))))
    )
)


;(nr_noduri '(a (b (c) (d (e))) (f (g))))
;  a (    b (c) (d (e))    )   (f (g))   )

;(nr_noduri '(a (b (d (e (f)))) (c (g (h (i (j (k (l)))))))))