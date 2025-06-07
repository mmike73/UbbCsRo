(defun inloc_atomi_k (l k crt)
    (cond
        ((and (atom l) (= k crt)) (list 0))
        ((atom l) (list l))
        (t (list (apply #'append (mapcar #'(lambda (lst) (inloc_atomi_k lst k (+ crt 1))) l))))
    )
)