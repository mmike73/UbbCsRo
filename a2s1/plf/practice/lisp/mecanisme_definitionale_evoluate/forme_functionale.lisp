(defun increment (x)
    (lambda (y)
        (+ x y)
    )
)

;; returneaza o noua functie (inchidere) care adauga 5 la argumentul sau
(setq inc5 (increment 5))

(print (funcall inc5 3))

(defun two_funs (x)
    (list
        (function (lambda () x))
        (function (lambda (y) (setq x y)))
    )
)

(setq funs1 (two_funs 6))
(setq funs2 (two_funs 5))

;;Break 7 [9]> (funcall (first funs1))
;;6
;;Break 7 [9]> (funcall (second funs1) - too few arguments
;;