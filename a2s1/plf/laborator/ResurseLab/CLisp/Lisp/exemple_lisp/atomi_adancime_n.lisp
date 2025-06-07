(defun lista (l n)
    (cond
        ((and (= n -1) (atom l)) (list l))
        ((= n -1) nil)
        ((atom l) nil)
        (t (mapcan #'(lambda (l) (lista l (- n 1))) l))
    )
)
;; nu se aplica la primul element, adica radacina
;; se aplica la subarbori,  care vor fi la adancime crt + 1