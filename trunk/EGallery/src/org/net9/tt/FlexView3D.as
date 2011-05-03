package org.net9.tt
{
	import away3d.cameras.Camera3D;
	import away3d.containers.View3D;
	import away3d.primitives.Sphere;
	
	import flash.events.Event;
	
	import mx.core.UIComponent;
	
	public class FlexView3D extends UIComponent
	{
		private var view:View3D;
		private var sphere:Sphere;
		
		public function FlexView3D()
		{
			super();
			this.addEventListener(Event.ENTER_FRAME, onFrameEnter);
		}
		
		override protected function createChildren():void
		{
			super.createChildren();
			
			if(!this.view)
			{
				view = new View3D({x:200,y:200});
				this.addChild(this.view);
			}
			
			if (!this.sphere) {
				sphere = new Sphere();
				this.view.scene.addChild(this.sphere);
			}
			
		}
		
		override protected function updateDisplayList(
			unscaledWidth:Number, unscaledHeight:Number):void
		{
			super.updateDisplayList(unscaledWidth, unscaledHeight);
			
			if(this.width / 2 != this.view.x)
				this.view.x = this.width / 2;
			if(this.height / 2 != this.view.y)
				this.view.y = this.height / 2;
		}
		
		private function onFrameEnter(event:Event):void
		{
			if(this.view && this.view.stage)
			{
				this.sphere.rotationX += .7;
				this.sphere.rotationY += .5;
				this.sphere.rotationZ += .4;
				
				this.view.render();
			}
		} 
	}
}