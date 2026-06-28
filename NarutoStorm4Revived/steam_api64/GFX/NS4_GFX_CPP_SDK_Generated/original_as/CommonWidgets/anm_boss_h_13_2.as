package result_main_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol144")]
   public dynamic class anm_boss_h_13 extends MovieClip
   {
      
      public var txt_head:smb_font;
      
      public function anm_boss_h_13()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_head.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_head.SetTextSize(33);
         this.txt_head.SetTextColor(smb_font.CCD_COLOR_WHITE);
      }
   }
}

