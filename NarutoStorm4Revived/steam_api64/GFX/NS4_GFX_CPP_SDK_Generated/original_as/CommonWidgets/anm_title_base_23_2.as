package result_main_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol130")]
   public dynamic class anm_title_base_23 extends MovieClip
   {
      
      public var txt_boss_sub:smb_font;
      
      public function anm_title_base_23()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_boss_sub.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_boss_sub.SetTextSize(40);
         this.txt_boss_sub.SetTextColor(smb_font.CCD_COLOR_WHITE);
      }
   }
}

