 'use strict';

var VALOR_NULO = '-';

var RotationDirection = {
	Clockwise: '0',
	CounterClockwise: '1'
};

var DiagramaFasorial = function (rotationDirection) {
	rotationDirection = rotationDirection || RotationDirection.CounterClockwise;
	initializeProperties.call(this, rotationDirection);
};

function initializeProperties(rotationDirection) {
	this.t = 750, //500
	this.x = 210, //140
	this.y = 210, //140
	this.r = 150, //100
	this.m = 60,  //40

	this.color = {
		red: {
			light: '#dc4e44',
			medium: '#c83025',
			dark: '#9d261d'
		},
		green: {
			light: '#86cb86',
			medium: '#62bc62',
			dark: '#46a546'
		},
		blue: {
			light: '#49c7fc',
			medium: '#17b8fb',
			dark: '#049cdb'
		},
	};

	this.rad = Math.PI / 180;
	this.rotationDirection = rotationDirection;
	this.paper = null;
	this.clockwise = isClockwise.bind(this);
}

function isClockwise() {
	return this.rotationDirection === RotationDirection.Clockwise;
}

function drawCircle() {
	this.paper.path('M' + this.m + ',' + this.y + 'L' + (this.r * 2 + this.m) + ',' + this.y).attr({ stroke: '#f0f0f0', 'stroke-width': 1 });
	this.paper.path('M' + this.x + ',' + this.m + 'L' + this.x + ',' + (this.r * 2 + this.m)).attr({ stroke: '#f0f0f0', 'stroke-width': 1 });
	this.paper.circle(this.x, this.y, this.r).attr({ fill: '#000', stroke: '#000', 'stroke-width': 1 });
}

function drawAngles() {
	var angle = 30,
		startangle = 0;

	if (this.clockwise()) {
		for (var i = 330; i >= 0; i -= angle) {
			drawAngle.call(this, angle, startangle, i);
			startangle -= angle;
		}
	}
	else {
		for (var i = angle; i <= 360; i += angle) {
			drawAngle.call(this, angle, startangle, i);
			startangle -= angle;
		}
	}
}

function drawAngle(angle, startangle, grades) {
	var endangle = startangle - angle;

	var text = grades;
	var fill = '#444';

	if (grades === 360) {
		text = '0';
	}
	if (grades % 90 === 0) {
		fill = '#fff';
	}

	this.paper.text(this.x + (this.r + 15) * Math.cos(endangle * this.rad), this.y + (this.r + 15) * Math.sin(endangle * this.rad), text)
		.attr({ fill: fill, 'font-size': 12 });
	startangle = endangle;
}

function drawVectors() {
	var va = this.paper.path('M' + this.x + ',' + this.y + 'L' + (this.x + this.r * 0.57) + ',' + this.y).attr({ stroke: this.color.red.dark, 'stroke-width': 1.5 }),
		vb = this.paper.path('M' + this.x + ',' + this.y + 'L' + (this.x + this.r * 0.57) + ',' + this.y).attr({ stroke: this.color.green.dark, 'stroke-width': 1.5 }),
		vc = this.paper.path('M' + this.x + ',' + this.y + 'L' + (this.x + this.r * 0.57) + ',' + this.y).attr({ stroke: this.color.blue.dark, 'stroke-width': 1.5 }),

		vab = this.paper.path('M' + this.x + ',' + this.y + 'L' + (this.x + this.r) + ',' + this.y).attr({ stroke: this.color.red.medium, 'stroke-width': 1.5 }),
		vbc = this.paper.path('M' + this.x + ',' + this.y + 'L' + (this.x + this.r) + ',' + this.y).attr({ stroke: this.color.green.medium, 'stroke-width': 1.5 }),
		vca = this.paper.path('M' + this.x + ',' + this.y + 'L' + (this.x + this.r) + ',' + this.y).attr({ stroke: this.color.blue.medium, 'stroke-width': 1.5 }),

		ia = this.paper.path('M' + this.x + ',' + this.y + 'L' + (this.x + this.r * 0.8) + ',' + this.y).attr({ stroke: this.color.red.light, 'stroke-width': 1.5, 'stroke-dasharray': '.' }),
		ib = this.paper.path('M' + this.x + ',' + this.y + 'L' + (this.x + this.r * 0.8) + ',' + this.y).attr({ stroke: this.color.green.light, 'stroke-width': 1.5, 'stroke-dasharray': '.' }),
		ic = this.paper.path('M' + this.x + ',' + this.y + 'L' + (this.x + this.r * 0.8) + "," + this.y).attr({ stroke: this.color.blue.light, 'stroke-width': 1.5, 'stroke-dasharray': '.' });

	return {
		va: va,
		vb: vb,
		vc: vc,

		vab: vab,
		vbc: vbc,
		vca: vca,

		ia: ia,
		ib: ib,
		ic: ic
	};
}

function draw() {
	this.paper.clear();
	drawCircle.call(this);
	drawAngles.call(this);
	return drawVectors.call(this);
}

function toggleRotationDirection() {
	var newRotation = this.clockwise() ? RotationDirection.CounterClockwise : RotationDirection.Clockwise;
	this.rotationDirection(newRotation);
}

DiagramaFasorial.prototype.init = function (container) {
	var div = container;
	this.paper = new Raphael(div, this.x + this.y, this.x + this.y);
	this.vetores = draw.call(this);
	return this.vetores;
};

DiagramaFasorial.prototype.rotate = function (vector, angle) {
	if (angle === VALOR_NULO) {
		vector.hide();
		return;
	}
	vector.show();
	angle *= this.clockwise() ? 1 : -1;
	vector.animate({ transform: 'r' + angle + ',' + this.x + ',' + this.y }, this.t, 'linear');
};

DiagramaFasorial.prototype.toggleRotationDirection = function () {
	toggleRotationDirection.call(this);
	this.vetores = draw.call(this);
};

DiagramaFasorial.prototype.refresh = function () {
	this.vetores = draw.call(this);
};
