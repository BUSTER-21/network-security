import sys
import argparse
from random import randint
from Crypto.Util.number import bytes_to_long, inverse, long_to_bytes


##encryption for message
def encryption(kpb, message):
	rp, alp, mex = kpb
	
	a = randint(0, rp) 
	
	## formula for Ephemeral key  eph = (alp^a)mod(rp)
	eph = pow(alp, a, rp)
	
	## formula for Shared key  sk = (mex^a)mod(rp)
	sk = pow(mex,a,rp)
	
	## formula for Encrypted message  em = (x*K)mod(p)
	em = (message*sk) % rp
	
	## person A sends the ephemeral key and encrypted message (Ke, y)
	sent_val = (eph, em)

  
	print ("Plaintext message:  "  + str(message) )

	print ("Public key: (" + str(rp) + "," + str(alp) + "," + str(mex) + ")" )
	
	print ("Shared key (sk):  "  + str(sk) )

	print ("Ephemeral key:  "  + str(eph) )
	
	print ("Encrypted message:  "  + str(em) )
	
	print ("Person A sends (eph,em):  (" + str(eph) + "," + str(em) + ")" )
	
	return sent_val


##decryption for messsage
def decryption(kpr, encrypted_message):

	rp, alp, b = kpr

	eph, em = encrypted_message
	
	## formula used for Shared key  sk = (eph^b)mod(rp)

	sk = pow(eph,b,rp)
	
	## formula used for Decrypted message x = (em*sk^(-1))mod(rp)
	
	x = (em*inverse(sk, rp)) % rp
	
	print ("Private key: (" + str(rp) + "," + str(alp) + "," + str(b) + ")" )
		
	print ("Alice receives (Ke,y): (" + str(eph) + "," + str(em) + ")" )
		
	print ("Shared key (sk):  "  + str(sk) )
		
	print ("Decrypted message:  "  + str(x) )
	
	return x


##function used for making key as public used by person A
def create_kpb(rp, alp, mex):

	rp=int(rp)
	
	alp=int(alp)
	
	mex=int(mex)
	
	kpb  = (rp, alp, mex) 
	
	return kpb


##function used for making key as private used by person A
def create_kpr(rp, alp, b):

	rp=int(rp)
	
	alp=int(alp)
	
	b=int(b)
	
	kpr=(rp, alp, b) 
	
	return kpr

##argument parsing from terminal
def get_args():
	
	parser = argparse.ArgumentParser()
	
	##encrypt argument
	parser.add_argument('-e', '--encrypt', required=False, action='store_true')
	
	##alfa parameter argument
	parser.add_argument('-a', '--alfa_parameter', required=True, action='store')
	
	##random integer parameter
	parser.add_argument('-rp', '--p_parameter', required=True, action='store')

	parser.add_argument('-B', '--B_parameter', required=False, action='store')
	
	parser.add_argument('-d', '--decrypt', required=False, action='store_true')

	parser.add_argument('-b', '--b_parameter', required=False, action='store')
	
	parser.add_argument('-eph','--ephemeral_key', required=False, action='store')

	parser.add_argument('-m', '--message', required=True, action='store')

	return parser.parse_args()

def main():
	myargs=get_args()
	
	m=int(myargs.message)
	

	##for encryption
	if myargs.encrypt:

		rp=myargs.p_parameter
	
		alp=myargs.alfa_parameter
	
		mex=myargs.B_parameter
	
		kpb=create_kpb(rp, alp, mex)
	
		encrypted_message=encryption(kpb, m)
	
		print(encrypted_message)


	##for decryption 
	elif myargs.decrypt:

		rp=myargs.p_parameter
	
		alp=myargs.alfa_parameter
	
		b=myargs.b_parameter
	
		eph=myargs.ephemeral_key
	
		kpr=create_kpr(rp, alp, b)
	
		eph=int(eph)
	
		encrypted_message=(eph, m)
	
		decrypted_message=decryption(kpr, encrypted_message)
	
		print(decrypted_message)
	

if __name__ == "__main__":
    main()
