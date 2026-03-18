def rc4_encrypt(plaintext, key_list, n_size=10):
    S = list(range(n_size))
    j = 0
    for i in range(n_size):
        j = (j + S[i] + key_list[i % len(key_list)]) % n_size
        S[i], S[j] = S[j], S[i]  
        
    i = 0
    j = 0
    keystream = []
    ciphertext_ascii = []
    ciphertext_chars = []
    
    for char in plaintext:
        i = (i + 1) % n_size
        j = (j + S[i]) % n_size
        S[i], S[j] = S[j], S[i]  
        
        K_t = S[(S[i] + S[j]) % n_size]
        keystream.append(K_t)
        
        cipher_byte = ord(char) ^ K_t
        ciphertext_ascii.append(cipher_byte)
        ciphertext_chars.append(chr(cipher_byte))
        
    return keystream, ciphertext_ascii, "".join(ciphertext_chars)

m = "cybersecurity"
K = [2, 4, 1, 7]

keystream, c_ascii, c_text = rc4_encrypt(m, K, n_size=10)

print(f"Ban ro: {m}")
print(f"Dong Khoa: {keystream}")
print(f"Ban Ma (Ma ASCII): {c_ascii}")
print(f"Ban Ma (Ky tu): {c_text}")