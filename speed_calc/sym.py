class sym(object):
    def __init__(self,stri):
        self.stri = stri

    def __mul__(self,a):
        if self.stri == a.stri:
            out = f'{self.stri}^2'
        else:
            if a.stri.find('+')!=-1:
                out=f'{self.stri}*({a.stri})'
            else:
                out=f'{self.stri}*{a.stri}'
        return(sym(out))
    
    def __imul__(self,a):
        if self.stri == a.stri:
            out = f'{self.stri}^2'
        else:
            out=f'{self.stri}*{a.stri}'
        return(sym(out))

    def __add__(self,a):
        if self.stri == "":
            out = f'{a.stri}'
        else:
            if self.stri == a.stri:
                out = f'2*{self.stri}'
            else:
                out = f'{self.stri}+{a.stri}'
        return(sym(out))

    def __iadd__(self,a):
        if self.stri == "":
            out = f'{a.stri}'
        else:
            if self.stri == a.stri:
                out = f'2*{self.stri}'
            else:
                out = f'{self.stri}+{a.stri}'
        return(sym(out))


    def __str__(self):
        return self.stri

    def split(self, token):
        return self.stri.split(token)

