(defun f(l)
    (max (car l) (caddr l))
)

(setq #'f 10)
(setq g 'f)
(funcall g '(8 11 2 3 7 9))