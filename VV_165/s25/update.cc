#include <math.h>
#include <stdio.h>
#include <iostream>
#include "humandata.h"
#include "human.h"

void human::update(int x) {
	stim(x, stim_here, extra_stim_here);
	revpots();
	rates(x);
	gates(x);
	currents(x);
	fluxbuf(x); /*Lucia 18-July-2011: I changed the order. fluxbuf was the first */
	voltage(x);
	dvdt(x);
	concentrations(x);
	ECG(x);
}
