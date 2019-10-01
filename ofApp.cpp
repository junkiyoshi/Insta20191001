#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(285);

	ofFill();
	ofSetColor(39);
	ofDrawSphere(glm::vec3(), 60);

	int width = 40;
	for (int len = 150; len < 320; len += width * 2) {

		for (int param = 0; param < 100; param++) {

			auto noise_location = this->make_point(len, param);
			auto next_noise_location = this->make_point(len, param + 1);

			int z = ofMap(ofNoise(noise_location.x * 0.0045, noise_location.y * 0.0045, ofGetFrameNum() * 0.005), 0, 1, -50, 50);
			int next_z = ofMap(ofNoise(next_noise_location.x * 0.0045, next_noise_location.y * 0.0045, ofGetFrameNum() * 0.005), 0, 1, -50, 50);

			z = (z / 10) * 10;
			next_z = (next_z / 10) * 10;

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3(this->make_point(len - width * 0.5, param), z));
			vertices.push_back(glm::vec3(this->make_point(len + width * 0.5, param), z));
			vertices.push_back(glm::vec3(this->make_point(len + width * 0.5, param + 1), next_z));
			vertices.push_back(glm::vec3(this->make_point(len - width * 0.5, param + 1), next_z));

			ofFill();
			ofSetColor(239);
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);

			ofNoFill();
			ofSetColor(39);
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}