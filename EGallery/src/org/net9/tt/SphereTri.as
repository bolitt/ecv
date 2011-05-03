package org.net9.tt
{
	import away3d.containers.*;
	import away3d.core.render.Renderer;
	import away3d.primitives.*;
	import away3d.test.Button;
	
	import flash.display.Sprite;
	import flash.display.StageAlign;
	import flash.display.StageScaleMode;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.Vector3D;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.utils.getTimer;
	
	[SWF(width="500", height="400", frameRate="60", backgroundColor="#FFFFFF")]
	public class SphereTri extends Sprite
	{
		private var View:View3D;
		private var baseObject:Sphere;
		private var planeComplexity:Number = 0;
		private var label2:TextField;
		private var lastTime:Number;
		
		public function SphereTri()
		{
			super();

			// prep for handling resizing events
			this.stage.scaleMode = StageScaleMode.NO_SCALE;
			this.stage.align = StageAlign.TOP;
			
			// create a 3D-viewport
			View = new View3D({x:250, y:200});
			View.renderer = Renderer.BASIC;
			addChild(View);
			
			View.camera.position = new Vector3D(400, 500, 400);
			View.camera.lookAt( new Vector3D(0, 0, 0) );
			baseObject = new Sphere({material:"red#",radius:150,segmentsW:6,segmentsH:4});
			View.scene.addChild(baseObject);
			
			addControls();
			addEventListener(Event.ENTER_FRAME, onEnterFrame);
		}
		
		private function onEnterFrame(e:Event):void
		{
			baseObject.rotationY += 1;
			var fps:Number = Math.floor( 1000/(getTimer()-lastTime) );
			label2.text = ( (6+planeComplexity)*(4+planeComplexity-1)*2 )+" Triangles (fps: "+fps+")";
			lastTime = getTimer();
			View.render();
		}
		
		private function addControls():void
		{
			var txtFormat:TextFormat = new TextFormat("_sans",12);
			var pad:Number = 10;
			var label1:TextField = new TextField();
			label1.x = pad;
			label1.y = pad;
			label1.height = 30;
			label1.width = 240;
			label1.defaultTextFormat = txtFormat;
			label1.text = "Increase/decrease complexity";
			
			label2 = new TextField();
			label2.defaultTextFormat = txtFormat;
			label2.x = pad;
			label2.y = pad;
			label2.height = 30;
			label2.width = 140;
			label2.y = 40;
			
			var plusButt:Button = new Button("+",20, 20);
			plusButt.addEventListener(MouseEvent.CLICK, increaseComplexity);
			plusButt.x = pad;
			plusButt.y = label2.height+label2.y;
			var minButt:Button = new Button("-",20, 20);
			minButt.addEventListener(MouseEvent.CLICK, decreaseComplexity);
			minButt.x = 50;
			minButt.y = label2.height+label2.y;
			
			addChild(label1);
			addChild(label2);
			addChild(plusButt);
			addChild(minButt);
		}
		private function decreaseComplexity(e:MouseEvent):void
		{
			planeComplexity > 0 ? planeComplexity -= 1 : planeComplexity = 0;
			baseObject.segmentsW = 6+planeComplexity;
			baseObject.segmentsH = 4+planeComplexity;
		}
		private function increaseComplexity(e:MouseEvent):void
		{
			planeComplexity += 1;
			baseObject.segmentsW = 6+planeComplexity;
			baseObject.segmentsH = 4+planeComplexity;
		}
	}
}