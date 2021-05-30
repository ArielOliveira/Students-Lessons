my_list = [57.05132, 71.0779, 99.13106, 113.15764, 113.15764, 115.0874, 129.11398, 97.11518, 101.10388, 87.0773]

print('length of my_list is ', len(my_list))

b=[]

for d in my_list:
    for e in my_list:
        for f in my_list:
            for g in my_list:
                for h in my_list:
                    b.append(d+e+f+g+h)
                    # if a[i]+a[j]+a[k]+a[l]+a[m] not in b:


print('length of b is ', len(b))
print()
myformattedlist = ["%.4f" % item for item in b]
#print(myformattedlist)
#c = list(dict.fromkeys(b))
c = set(myformattedlist)
print(c)
print('length of duplicateless b is ', len(c))