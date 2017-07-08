#include "GraphFunctions.h"
#include "../Widgets/Graph.h"
#include <limits>

std::vector< std::pair<Widget*, float> > *AppRef::widgetsPtr = nullptr;

double f_graph(Namescope* ns, const std::vector<std::shared_ptr<Value>>& args)
{
	Graph *graph = new Graph();
	auto arg1 = (TypedValue<std::string>*)args[0].get();
	auto arg2 = (TypedValue<double>*)args[1].get();
	auto arg3 = (TypedValue<double>*)args[2].get();
	graph->init(arg1->value, arg2->value, arg3->value, ns);
	AppRef::widgetsPtr->push_back(std::make_pair(graph, 10.f));
	return std::numeric_limits<double>::max();
}