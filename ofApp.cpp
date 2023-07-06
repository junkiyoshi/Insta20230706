#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(200, 6);
	this->mesh = ico_sphere.getMesh();
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clearColors();
	ofSeedRandom(39);

	ofColor color;
	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		auto noise_value = ofMap(ofNoise(glm::vec4(this->mesh.getVertex(i) * 0.005, ofGetFrameNum() * 0.015)), 0, 1, 0, 10);
		int int_noise_value = (int)noise_value;
		
		noise_value = noise_value - int_noise_value;
		auto brightness = ofMap(abs(noise_value - 0.5), 0, 0.5, 255, 0);
		auto hue = ofMap(int_noise_value, 0, 10, 0, 255);
		color.setHsb(hue, 100, brightness);
		this->mesh.addColor(color);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 3);

	this->mesh.drawFaces();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}