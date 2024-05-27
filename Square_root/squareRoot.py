# swift pow(base,exponent) % modulus from right to left
def pow1(base, exponent, modulus): 

	result = 1 
	base = base % modulus 
	while (exponent > 0): 
		if (exponent % 2 == 1):
			result = (result * base) % modulus 
		exponent = int(exponent) >> 1 
		base = (base * base) % modulus 

	return result

# the order of an element
def order(p, b):  
	k = 3
	while (True): 
		if (pow1(b, k, p) == 1): 
			return k 
		k += 1

# represent p-1 as q * 2^(s)
def convertq2s(q):
	s = 0 
	while (q % 2 == 0):
		q = q / 2
		s += 1 
		
	return [q, s] 


def TonelliSh(n, p): 

    # Euler’s criterion
    if (pow1(n, (p - 1) / 2, p) == (p - 1)): 
	    return -1

    ar = convertq2s(p - 1)
    q = ar[0] # the odd part
    s = ar[1] # the degree of 2
    
    if (s == 1):
        return [pow1(n,int((p+1)/4),p), p - pow1(n,int((p+1)/4),p)]

	# finding smallest z such that 
	# z ^ ((p - 1) / 2) (mod p) = p - 1 
    z = 2
    while (True):
        if (pow1(z, (p - 1) / 2, p) == (p - 1)): 
            break
        z += 1
    
    c = pow1(z,q,p)
    r = pow1(n, int((q + 1) / 2), p)
    t = pow1(n,q,p)
    m = s

    while (True):
        if (t == 1):
            return [r, p - r]
        i = 1
        while ((pow1(t, pow(2,i), p) != 1) and (i < m) ):
            i += 1
        b = pow1(c, pow(2, m - i - 1), p)
        r = (r * b) % p
        t = (t * b * b) % p
        c = (b*b) % p
        m = i


n, p = map(lambda x : int(x), input().split()) 

x = TonelliSh(n, p)

if (x == -1): 
	print("Modular square root does not exist\n") 
else:
	print("Modular square root of ", n, 
		" in Z_", p, " is ", x, sep = '')
