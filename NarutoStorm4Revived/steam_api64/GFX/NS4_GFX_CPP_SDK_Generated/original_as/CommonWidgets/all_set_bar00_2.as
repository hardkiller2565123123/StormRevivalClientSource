package script.freebtl_set
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_base4;
   import script.xcmn_menu.nut_base5;
   import script.xcmn_menu.nut_cursor_m;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol26")]
   public class all_set_bar00 extends MovieClip
   {
      
      public var mc_base1:nut_base4;
      
      public var mc_base2:nut_base5;
      
      public var mc_cursor_l:nut_cursor_m;
      
      public var mc_cursor_r:nut_cursor_m;
      
      public var mc_sel1:MovieClip;
      
      public var mc_sel2:MovieClip;
      
      public var txt_set:smb_font;
      
      public var txt_title_set00:smb_font;
      
      public function all_set_bar00()
      {
         var _loc2_:Point = null;
         var _loc3_:smb_font = null;
         var _loc4_:MovieClip = null;
         var _loc5_:MovieClip = null;
         var _loc6_:MovieClip = null;
         var _loc7_:MovieClip = null;
         var _loc8_:Number = NaN;
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
         var _loc1_:smb_font = this["txt_title_set00"];
         if(_loc1_ != null && _loc1_.IsArabic() == true)
         {
            _loc2_ = new Point();
            _loc1_.GetTextPos(_loc2_);
            _loc1_.SetTextPos(-_loc2_.x,_loc2_.y);
            _loc3_ = this["txt_set"];
            if(_loc3_ != null)
            {
               _loc3_.GetTextPos(_loc2_);
               _loc3_.SetTextPos(-_loc2_.x,_loc2_.y);
            }
            _loc4_ = this["mc_base2"];
            if(_loc4_ != null)
            {
               _loc4_.x *= -1;
            }
            _loc5_ = this["mc_base1"];
            if(_loc5_ != null)
            {
               _loc5_.x *= -1;
            }
            _loc6_ = this["mc_cursor_l"];
            _loc7_ = this["mc_cursor_r"];
            if(_loc6_ != null && _loc7_ != null)
            {
               _loc8_ = _loc6_.x;
               _loc6_.x = -_loc7_.x;
               _loc7_.x = -_loc8_;
            }
         }
      }
      
      internal function frame1() : *
      {
         stop();
         if(this.txt_title_set00.IsArabic() == true)
         {
            this.txt_title_set00.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.txt_title_set00.SetTextPivot(smb_font.CCD_PIVOT_RC);
         }
         else
         {
            this.txt_title_set00.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_title_set00.SetTextSize(33);
         this.txt_title_set00.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_title_set00.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_title_set00.SetTextFieldWidth(740);
         this.txt_title_set00.SetTextFit(true);
         this.txt_set.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_set.SetTextSize(33);
         this.txt_set.SetTextColor(11606272);
         this.txt_set.SetDropShadowFilter(11645361);
         this.txt_set.SetTextFieldWidth(640);
         this.txt_set.SetTextFit(true);
         this.mc_base2.alpha = 1;
      }
      
      internal function frame2() : *
      {
         stop();
         if(this.txt_title_set00.IsArabic() == true)
         {
            this.txt_title_set00.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.txt_title_set00.SetTextPivot(smb_font.CCD_PIVOT_RC);
         }
         else
         {
            this.txt_title_set00.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_title_set00.SetTextSize(33);
         this.txt_title_set00.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_title_set00.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_title_set00.SetTextFieldWidth(740);
         this.txt_title_set00.SetTextFit(true);
         this.txt_set.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_set.SetTextSize(33);
         this.txt_set.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_set.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_set.SetTextFieldWidth(640);
         this.txt_set.SetTextFit(true);
         this.mc_base2.alpha = 0;
      }
      
      internal function frame3() : *
      {
         stop();
         if(this.txt_title_set00.IsArabic() == true)
         {
            this.txt_title_set00.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.txt_title_set00.SetTextPivot(smb_font.CCD_PIVOT_RC);
         }
         else
         {
            this.txt_title_set00.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_title_set00.SetTextSize(33);
         this.txt_title_set00.SetTextColor(5592405);
         this.txt_title_set00.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_title_set00.SetTextFieldWidth(740);
         this.txt_title_set00.SetTextFit(true);
         this.txt_set.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_set.SetTextSize(33);
         this.txt_set.SetTextColor(5592405);
         this.txt_set.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_set.SetTextFieldWidth(640);
         this.txt_set.SetTextFit(true);
         this.mc_base2.alpha = 0;
      }
   }
}

