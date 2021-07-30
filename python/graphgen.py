"""
Ensemble de fonctions destinés à un affichage simplifié de fonctions avec matplotlib.
	-> graph2D() permet de tracer un graphe simple. Des paramètres peuvent être fournis (voir help("graph2D")).
	-> multgraph2D() permet de tracer plusieurs courbes sur un graphe simple. Les paramètres peuvent être fournis sous forme de tableau.
	-> graph2Dbiax() permet de tracer une courbe sur un graphe avec 2 axes. Les paramètres peuvent être fournis sous forme de tableau.
	-> graph3D() permet de tracer un imshow(). Permet aussi si out=True d'envoyer en sortie fig,ax pour réaliser un autre tracé.
"""

import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import math as math

mpl.rcParams.update({'font.size': 30})
#mpl.rcParams.update({'legend.loc' : 'best'})
mpl.rcParams.update({'text.usetex' : True})
mpl.rcParams.update({"figure.figsize" : (8, 8)})
#plt.gcf().subplots_adjust(bottom = 0.2 , left = 0.15)

xarr = [j for j in range(0, 100)]
yarr = [x**2 for x in xarr]
yarr2 = [x**3 for x in xarr]

def help(function):
	if(function == "graph2D"):
		print("Paramètres : show, legend, invert, width, style, color, label, xlabel, ylabel, xmin, xmax, ymin, ymax, badjust, ladjust, radjust, tajust, ent, out")
	if(function == "graph3D"):
		print("Paramètres : show, colorbar, cmap, gray, vmin, vmax, xmin, xmax, ymin, ymax, xlabel, ylabel, colorbarlabel, badjust, ladjust, radjust, tajust, out")
		
def value(params, param, defparam, num):
	if type(params.get(param, defparam)) is list:
		if(num>=len(params.get(param, defparam))):
			return params.get(param, defparam)[-1]
		else:
			return params.get(param, defparam)[num]
	else:
		return params.get(param, defparam)
		
def grayify_cmap(cmap):
    """Return a grayscale version of the colormap. Source: https://jakevdp.github.io/blog/2014/10/16/how-bad-is-your-colormap/"""
    cmap = plt.cm.get_cmap(cmap)
    colors = cmap(np.arange(cmap.N))
    
    # convert RGBA to perceived greyscale luminance
    # cf. http://alienryderflex.com/hsp.html
    RGB_weight = [0.299, 0.587, 0.114]
    luminance = np.sqrt(np.dot(colors[:, :3] ** 2, RGB_weight))
    colors[:, :3] = luminance[:, np.newaxis]
    
    return cmap.from_list(cmap.name + "_grayscale", colors, cmap.N)

def graph2D(xdata, ydata, **params):
	if params.get("ent", "none")=="none":
		fig,ax = plt.subplots()
	else:
		ax = params.get("ent", "none")
	xmin = params.get("xmin", 0);
	xmax = params.get("xmax", 0);
	ymin = params.get("ymin", 0);
	ymax = params.get("ymax", 0);
	if (xmin==xmax) and (ymin==ymax):
		ax.autoscale()
	elif xmin==xmax:
		ax.autoscale()
		ax.set_ylim(min(ymin, ymax), max(ymin, ymax))
	elif ymin==ymax:
		ax.autoscale()
		ax.set_xlim(min(xmin, xmax), max(xmin, xmax))
	else:
		ax.set_xlim(min(xmin, xmax), max(xmin, xmax))
		ax.set_ylim(min(ymin, ymax), max(ymin, ymax))
	plt.gcf().subplots_adjust(bottom=params.get("badjust", 0.1), left=params.get("ladjust", 0.1), right=params.get("radjust", 0.9), top=params.get("tadjust", 0.9))
	if(params.get("invert", False)==False):
		ax.plot(xdata, ydata, linewidth = params.get("width", 1), label = params.get("label", ""), linestyle = params.get("style", "-"), color = (params.get("color", (0., 0., 0.))))
	elif(params.get("invert", False)==True):
		ax.plot(ydata, xdata, linewidth = params.get("width", 1), label = params.get("label", ""), linestyle = params.get("style", "-"), color = (params.get("color", (0., 0., 0.))))
	if(params.get("legend", True)==True):
		ax.legend()
	if(params.get("xlabel", "")!=""):
		ax.set_xlabel(params.get("xlabel", ""))
	if(params.get("ylabel", "")!=""):
		ax.set_ylabel(params.get("ylabel", ""))
	if(params.get("show", True)==True):
		plt.show(block=False)
	if params.get("out", False) == True:
		return ax
		
def multgraph2D(xdata, ydatas, **params):
	if params.get("ent", "none")=="none":
		fig,ax = plt.subplots()
	else:
		ax = params.get("ent", "none")
	for i in range(len(ydatas)):
		graph2D(xdata, ydatas[i], show=False, legend=False, width=value(params, "width", 1, i), style=value(params, "style", "-", i), color=value(params, "color", (0., 0., 0.), i), label=value(params, "label", "", i), ent=ax, invert = params.get("invert", False))
	xmin = params.get("xmin", 0);
	xmax = params.get("xmax", 0);
	ymin = params.get("ymin", 0);
	ymax = params.get("ymax", 0);
	if (xmin==xmax and xmin==0) and (ymin==ymax and ymin==0):
		ax.autoscale()
	elif xmin==xmax and xmin==0:
		ax.autoscale(axis="x")
		ax.set_ylim(min(ymin, ymax), max(ymin, ymax))
	elif ymin==ymax and ymin==0:
		ax.autoscale(axis="y")
		ax.set_xlim(min(xmin, xmax), max(xmin, xmax))
	else:
		ax.set_xlim(min(xmin, xmax), max(xmin, xmax))
		ax.set_ylim(min(ymin, ymax), max(ymin, ymax))
	plt.gcf().subplots_adjust(bottom=params.get("badjust", 0.1), left=params.get("ladjust", 0.1), right=params.get("radjust", 0.9), top=params.get("tadjust", 0.9))
	if(params.get("legend", True)==True):
		ax.legend()
	if(params.get("xlabel", "")!=""):
		ax.set_xlabel(params.get("xlabel", ""))
	if(params.get("ylabel", "")!=""):
		ax.set_ylabel(params.get("ylabel", ""))
	if(params.get("show", True)==True):
		plt.show(block=False)
	if params.get("out", False) == True:
		return ax

def graph2Dbiax(xdata, ydata1, ydata2, **params):
	fig,ax1 = plt.subplots()
	ax2 = ax1.twinx()
	xmin = params.get("xmin", 0)
	xmax = params.get("xmax", 0)
	ymin1 = value(params, "ymin", 0, 0)
	ymax1 = value(params, "ymax", 0, 0)
	ymin2 = value(params, "ymin", 0, 1)
	ymax2 = value(params, "ymax", 0, 1)
	if xmin==xmax and xmin==0:
		ax1.autoscale(axis="x")
		ax2.autoscale(axis="x")
	else:
		ax1.set_xlim(min(xmin, xmax), max(xmin, xmax))
		ax2.set_xlim(min(xmin, xmax), max(xmin, xmax))
	if ymin1==ymax1 and ymin1==0:
		ax1.autoscale(axis="y")
	else:
		ax1.set_ylim(min(ymin1, ymax1), max(ymin1, ymax1))
	if ymin2==ymax2 and ymin2==0:
		ax2.autoscale(axis="y")
	else:
		ax2.set_ylim(min(ymin2, ymax2), max(ymin2, ymax2))
	plt.gcf().subplots_adjust(bottom=params.get("badjust", 0.1), left=params.get("ladjust", 0.1), right=params.get("radjust", 0.9), top=params.get("tadjust", 0.9))
	c1 = value(params, "color", (0., 0., 0.), 0)
	c2 = value(params, "color", (0., 0., 0.), 1)
	ax1.set_xlabel(params.get("xlabel", ""))
	ax1.set_ylabel(value(params, "ylabel", "", 0), color=c1)
	ax2.set_ylabel(value(params, "ylabel", "", 1), color=c2)
	ax1.plot(xdata, ydata1, linewidth = value(params, "width", 1, 0), linestyle=value(params, "style", "-", 0), color=c1, label=value(params, "label", "", 0))
	ax2.plot(xdata, ydata2, linewidth = value(params, "width", 1, 1), linestyle=value(params, "style", "-", 1), color=c2, label=value(params, "label", "", 1))
	ax1.tick_params(axis='y', labelcolor=c1)
	ax2.tick_params(axis='y', labelcolor=c2)
	if(params.get("legend", True)==True):
		fig.legend(loc="upper left", bbox_to_anchor=(0,1), bbox_transform=ax1.transAxes)
	if(params.get("show", True)==True):
		plt.show(block=False)

def graph3D(data, **params):
	fig,ax = plt.subplots()
	cmap = params.get("cmap", "veridis")
	if(params.get("gray", False)):
		cmap = grayify_cmap(params.get("cmap", "veridis"))
	if params.get("vmin", "none")=="none" or params.get("vmax", "none")=="none":
		m=ax.imshow(data, extent = [params.get("xmin", -1), params.get("xmax", 1), params.get("ymin", -1), params.get("ymax", 1)], aspect="auto", interpolation="bicubic", origin="lower", cmap=cmap)
	else:
		m=ax.imshow(data, vmin = params.get("vmin", "none"), vmax = params.get("vmax", "none"), extent = [params.get("xmin", -1), params.get("xmax", 1), params.get("ymin", -1), params.get("ymax", 1)], aspect="auto", interpolation="bicubic", origin="lower", cmap=cmap)
	plt.gcf().subplots_adjust(bottom=params.get("badjust", 0.1), left=params.get("ladjust", 0.1), right=params.get("radjust", 0.9), top=params.get("tadjust", 0.9))
	if params.get("xlabel", "")!="":
		plt.xlabel(params.get("xlabel", ""))
	if params.get("ylabel", "")!="":
		plt.ylabel(params.get("ylabel", ""))
	if params.get("colorbar", True)==True:

		cbar = fig.colorbar(m)
		if params.get("colorbarlabel", "")!="":
			cbar.set_label(params.get("colorbarlabel", ""))
	if params.get("show", True)==True:
		plt.show(block=False)
	if params.get("out", False) == True:
		return ax

