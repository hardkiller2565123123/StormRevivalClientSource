package collect_skin_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_base4;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol9")]
   public dynamic class smb_cmn_title_8 extends MovieClip
   {
      
      public var all_base4:nut_base4;
      
      public var txt_title:smb_font;
      
      public function smb_cmn_title_8()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_title.SetTextColor(14013909);
         this.txt_title.SetTextFieldWidth(360);
         this.txt_title.SetTextSize(30);
      }
   }
}

