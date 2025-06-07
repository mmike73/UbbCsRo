(defun adancime (l)
    (cond
        ((null (cdr l)) 0)
        (t (+ 1 (apply #'max (mapcar #'adancime (cdr l)))))
    )
)


;; (adancime '(a (b (d (e (f)))) (c (g (h (i (j (k (l)))))))))