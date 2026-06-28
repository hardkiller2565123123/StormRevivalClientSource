package modesel_fla
{
   import flash.display.MovieClip;
   import script.xcp_cursor2.smb_crsr2;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public dynamic class anm_cursor_3 extends MovieClip
   {
      
      public var mc_cursor_t:smb_crsr2;
      
      public function anm_cursor_3()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
   }
}

