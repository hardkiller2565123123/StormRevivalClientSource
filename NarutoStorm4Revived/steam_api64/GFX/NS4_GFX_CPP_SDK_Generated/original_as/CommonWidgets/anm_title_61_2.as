package hist_cmn_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol43")]
   public dynamic class anm_title_61 extends MovieClip
   {
      
      public var all_title:MovieClip;
      
      public var txt_title:smb_font;
      
      public function anm_title_61()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_title.SetTextSize(38);
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_title.SetTextFieldWidth(640);
         this.txt_title.SetTextFit(true);
         this.txt_title.SetTextColor(16747598);
      }
      
      internal function frame2() : *
      {
         this.txt_title.SetTextColor(8111871);
      }
      
      internal function frame3() : *
      {
         this.txt_title.SetTextColor(13401087);
      }
   }
}

