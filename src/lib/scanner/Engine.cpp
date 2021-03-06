/*
 * Engine.cpp
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#include "Engine.h"
#include "../projector/Projector.h"

namespace threescanner {

Engine::Engine(const Config&) :
				input_(nullptr),
				cloud_(new PointCloud()) {

}

Engine::~Engine() {
	if (projector_ != nullptr && projectorFuture_.valid()) {
		projector_->stop();
	}
}

void Engine::setInput(ImageInputPtr input) {
	if (input_.get() != nullptr) {
		throw std::invalid_argument("Engine: cannot set input if already defined.");
	}
	input_ = input;
}

PointCloud::ConstPtr Engine::getCloud() const {
	return cloud_;
}

std::future<void> Engine::scan() {
	return std::async(std::launch::async, [this]() {
		this->scanSync();
	});
}

void Engine::connectProjector(ProjectorPtr projector) {
	projector_ = projector;
	projectorFuture_ = projector_->start();
}

} /* namespace threescanner */
