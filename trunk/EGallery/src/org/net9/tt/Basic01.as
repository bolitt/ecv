package org.net9.tt
{

	import away3d.containers.View3D;
	import away3d.primitives.Sphere;
	
	import flash.display.Sprite;
	import flash.events.Event;
	
	
	public class Basic01 extends Sprite
	{
		public var view:View3D;
		
		public function Basic01()
		{
			view = new View3D({x:200,y:200});
			addChild(view);
			
			var sphere:Sphere = new Sphere();
			view.scene.addChild(sphere);

			addEventListener(Event.ENTER_FRAME, onEnterFrame);
		}
		
		private function onEnterFrame(e:Event):void
		{
			view.render();
		}
		
	}
}