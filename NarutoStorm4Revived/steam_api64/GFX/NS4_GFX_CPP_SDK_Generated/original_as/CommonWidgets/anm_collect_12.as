package start_memory_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol36")]
   public dynamic class anm_collect_12 extends MovieClip
   {
      
      public var txt_collect:smb_font;
      
      public function anm_collect_12()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_collect.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_collect.SetTextSize(28);
         this.txt_collect.SetTextColor(16771961);
         this.txt_collect.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

