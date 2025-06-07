(defun nrap (e l)
    (cond
        ((equal L e) 1)
        ((atom L) 0)
        (t (apply #'+ (mapcar #'(lambda (L) (nrap e L)) l)))
    )
)

;; se foloseste lambda deoarece se doreset aplicarea functei la fiecare
;; element al listei l

;(nrap 4 '(1 2 3 4 4 5 6 4 5 3 (4 (4 5 ( 6 4 (4 (4)))))))