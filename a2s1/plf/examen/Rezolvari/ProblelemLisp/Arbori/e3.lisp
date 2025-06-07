(defun nr_nofuri_nivel_k (arb k)
    (nr_noduri_nivel_k_helper arb k 0)
)

(defun nr_noduri_nivel_k_helper (arb k crt)
    (cond
        ((null arb) 0)
        ((and (equal k crt) (atom arb)) 1)
        ((atom arb) 0)
        (t (apply #'+ (mapcar #'(lambda (subarb) (nr_noduri_nivel_k_helper subarb k (+ crt 1))) arb)))
    )
)
