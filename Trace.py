import matplotlib.pyplot as plt
import pandas as pd


f = pd.read_csv("Resultats.csv", sep=" ")


plt.subplot(2, 2, 1)
plt.plot(f["temps"], f["parametre"])
plt.xlabel("temps (s)")
plt.ylabel("paramètre d'ordre")


f["distance_barycentrex"] = (f["barycentrex"] - f["x"])
f["distance_barycentrey"] = (f["barycentrey"] - f["y"])

plt.subplot(2, 2, 3)
plt.plot(f["temps"], f[["distance_barycentrex", "distance_barycentrey"]], label=("x","y"))
plt.legend()
plt.xlabel("temps (s)")
plt.ylabel("distance au barycentre")

plt.subplot(2, 2, 4)
plt.scatter(f["distance_barycentrex"], f["vx"], c = f["temps"])
plt.colorbar()
plt.xlabel("distance au barycentre sur x")
plt.ylabel("vx")

plt.show()

