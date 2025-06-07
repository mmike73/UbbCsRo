(defun f (L e)
    (list e L)
)

(setq L '(1 2 3))
(setq e 4)

(mapcar #'f L e) ;;;?????????
(mapcar #'(lambda (L) (f L e)) L) 