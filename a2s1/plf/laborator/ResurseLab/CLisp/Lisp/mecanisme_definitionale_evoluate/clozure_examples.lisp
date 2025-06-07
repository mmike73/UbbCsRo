>   (defun f()
         10
    )

>   (f)
10

>   (setq f '11)
11

>   (f)
10

>   f
11

>   (setq g '7)
7

>   (function g)
;; efectiv ce e g

>   (function h)
undefined-function h

>   'G
G

>   (quote G)
G

>   (function car)
#<SYSTEM-FUNCTION CAR>

>   (function (lambda (l) (cdr l)))
#<FUNCTION :LAMBDA (L) (CDR L)>
#<CLOSURE :LAMBDA (L) (CDR L)> ;; DE CE NU E CLOSURE?

>   (function not)
#<SYSTEM-FUNCTION NOT>

>   (function and)
undefined function AND

>   (function or)
undefined function OR
