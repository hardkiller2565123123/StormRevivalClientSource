package net_bonus_fla
{
   import flash.display.MovieClip;
   import flash.events.Event;
   import script.xcmn_eff2.smb_xef_sun1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol11")]
   public dynamic class anm_flash2_3 extends MovieClip
   {
      
      public var mc_flash2:smb_xef_sun1;
      
      public function anm_flash2_3()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      public function fl_RotateContinuously_4(param1:Event) : *
      {
         this.mc_flash2.rotation += 0.5;
      }
      
      internal function frame1() : *
      {
         this.mc_flash2.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_4);
      }
   }
}

