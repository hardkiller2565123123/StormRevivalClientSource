package start_evnt_s_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol28")]
   public dynamic class anm_nambase_s_9 extends MovieClip
   {
      
      public var txt_num:smb_font;
      
      public function anm_nambase_s_9()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_num.SetTextSize(31);
         this.txt_num.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_num.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

