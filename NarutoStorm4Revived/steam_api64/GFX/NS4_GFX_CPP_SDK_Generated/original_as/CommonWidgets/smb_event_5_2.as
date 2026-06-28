package net_top_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public dynamic class smb_event_5 extends MovieClip
   {
      
      public var txt_event:smb_font;
      
      public function smb_event_5()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_event.SetTextSize(20);
         this.txt_event.SetTextColor(16770048);
         this.txt_event.DisableDropShadowFilter();
      }
   }
}

