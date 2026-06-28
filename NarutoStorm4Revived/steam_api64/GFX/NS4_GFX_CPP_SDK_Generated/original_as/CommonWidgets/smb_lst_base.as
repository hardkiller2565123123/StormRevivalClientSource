package script.map_sm
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol51")]
   public class smb_lst_base extends MovieClip
   {
      
      public var txt_lst_m:smb_font;
      
      public function smb_lst_base()
      {
         var _loc1_:Point = null;
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
         if(this.txt_lst_m.IsArabic() == true)
         {
            _loc1_ = new Point();
            this.txt_lst_m.GetTextPos(_loc1_);
            this.txt_lst_m.SetTextPos(-_loc1_.x,_loc1_.y);
         }
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_lst_m.SetTextStandardAlignByLanguage();
         this.txt_lst_m.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_lst_m.SetTextSize(30);
         this.txt_lst_m.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_lst_m.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_lst_m.SetTextFieldWidth(388);
         if(this.txt_lst_m.IsArabic() == true)
         {
            this.txt_lst_m.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.txt_lst_m.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
         }
      }
      
      internal function frame2() : *
      {
         this.stop();
         this.txt_lst_m.SetTextStandardAlignByLanguage();
         this.txt_lst_m.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_lst_m.SetTextSize(30);
         this.txt_lst_m.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_lst_m.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_lst_m.SetTextFieldWidth(388);
         if(this.txt_lst_m.IsArabic() == true)
         {
            this.txt_lst_m.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.txt_lst_m.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
         }
      }
      
      internal function frame3() : *
      {
         this.stop();
         this.txt_lst_m.SetTextStandardAlignByLanguage();
         this.txt_lst_m.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_lst_m.SetTextSize(30);
         this.txt_lst_m.SetTextColor(7566195);
         this.txt_lst_m.SetTextFieldWidth(388);
         if(this.txt_lst_m.IsArabic() == true)
         {
            this.txt_lst_m.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.txt_lst_m.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
         }
      }
   }
}

