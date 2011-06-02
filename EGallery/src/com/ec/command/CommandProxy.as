package com.ec.command
{
	import com.ec.ds.Direction;
	import com.ec.ui.AnimationComponent;
	import com.ec.log.Logger;
	import com.ec.app.EditPlayer;

	public class CommandProxy
	{
		private var _logger:Logger = null;
		private var _target:EditPlayer = null;
		
		protected function get animationComponent(): AnimationComponent
		{
			return _target.animationComponent;
		}
		
		public function CommandProxy(editPlayer:EditPlayer)
		{
			_logger = Logger.getInstance("CommandProxy");
			_target = editPlayer;
		}
		
		public function invoke(command:String, ...arguments) : void
		{
			_logger.debug(command + "|" + arguments.join("+"));
			if (command in this) {
				_logger.debug("Exists:" + command);
				_logger.debug("Is:" + this[command]);
				var f:Function = (this[command] as Function);
				if (f != null) {
					f.apply(this, arguments);
				}
			} else {
				_logger.debug("Not exits:" + command);
			}
		}
		
		public function roll(direction: String): void 
		{
			const valid:Object = {"LEFT":1, "RIGHT":1,
							      "DOWN":1, "UP":1};
			_logger.debug("roll|" + direction);
			_logger.debug("[]: " + valid);
			if (direction in valid) {
				animationComponent.roll(direction);
			} else {
				_logger.warning("Parameters invalid");
			}
		}
		
		public function animateRoll(direction: String): void 
		{
			const valid:Object = {"LEFT":1, "RIGHT":1,
								  "DOWN":1, "UP":1};
			_logger.debug("animateRoll|" + direction);
			_logger.debug("[]: " + valid);
			if (direction in valid) {
				animationComponent.animateRoll(direction);
			} else {
				_logger.warning("Parameters invalid");
			}
		}
	}
}