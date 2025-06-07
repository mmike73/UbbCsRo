(defun inloc_nod (arb e k ncrt)
    (cond
        ((null arb) nil)
        ((and (atom arb) (= ncrt k)) (list e))
        ((atom arb) (list arb))
        (t (list (apply #'append (mapcar #'(lambda (l) (inloc_nod l e k (+ ncrt 1))) arb))))
    )
)