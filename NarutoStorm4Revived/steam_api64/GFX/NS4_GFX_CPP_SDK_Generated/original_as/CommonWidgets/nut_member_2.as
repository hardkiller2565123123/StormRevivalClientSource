package script.freebtl_set
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_base4;
   import script.xcmn_menu.nut_base5;
   import script.xcmn_menu.nut_base6;
   import script.xcmn_menu.nut_cursor_m;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol19")]
   public class nut_member extends MovieClip
   {
      
      public var all_cursor_l1:nut_cursor_m;
      
      public var all_cursor_l2:nut_cursor_m;
      
      public var all_cursor_r1:nut_cursor_m;
      
      public var all_cursor_r2:nut_cursor_m;
      
      public var mc_base1:nut_base4;
      
      public var mc_base2:nut_base5;
      
      public var mc_base3:nut_base6;
      
      public var mc_blue:MovieClip;
      
      public var mc_member_4p:MovieClip;
      
      public var mc_member_8p:MovieClip;
      
      public var mc_red:MovieClip;
      
      public var mc_sel1:MovieClip;
      
      public var mc_sel2:MovieClip;
      
      public var txt_com:smb_font;
      
      public var txt_join:smb_font;
      
      public var txt_set:smb_font;
      
      public var txt_title_set00:smb_font;
      
      public function nut_member()
      {
         var _loc2_:Point = null;
         var _loc3_:smb_font = null;
         var _loc4_:MovieClip = null;
         var _loc5_:MovieClip = null;
         var _loc6_:Number = NaN;
         var _loc7_:MovieClip = null;
         var _loc8_:MovieClip = null;
         var _loc9_:MovieClip = null;
         var _loc10_:MovieClip = null;
         var _loc11_:smb_font = null;
         var _loc12_:smb_font = null;
         var _loc13_:MovieClip = null;
         var _loc14_:MovieClip = null;
         var _loc15_:MovieClip = null;
         var _loc16_:Point = null;
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3,3,this.frame4);
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
            _loc4_ = this["all_cursor_l1"];
            _loc5_ = this["all_cursor_r1"];
            _loc6_ = 0;
            if(_loc4_ != null && _loc5_ != null)
            {
               _loc6_ = _loc5_.x;
               _loc5_.x = -_loc4_.x;
               _loc4_.x = -_loc6_;
            }
            _loc4_ = this["all_cursor_l2"];
            _loc5_ = this["all_cursor_r2"];
            if(_loc4_ != null && _loc5_ != null)
            {
               _loc6_ = _loc5_.x;
               _loc5_.x = -_loc4_.x;
               _loc4_.x = -_loc6_;
            }
            _loc7_ = this["mc_base2"];
            if(_loc7_ != null)
            {
               _loc7_.x *= -1;
            }
            _loc8_ = this["mc_base1"];
            if(_loc8_ != null)
            {
               _loc8_.x *= -1;
            }
            _loc9_ = this["mc_member_4p"];
            if(_loc9_ != null)
            {
               _loc9_.x *= -1;
            }
            _loc10_ = this["mc_member_8p"];
            if(_loc10_ != null)
            {
               _loc10_.x *= -1;
            }
            _loc11_ = this["txt_join"];
            _loc12_ = this["txt_com"];
            if(_loc11_ != null && _loc12_ != null)
            {
               _loc16_ = new Point();
               _loc11_.GetTextPos(_loc2_);
               _loc12_.GetTextPos(_loc16_);
               _loc11_.SetTextPos(-_loc16_.x,_loc16_.y);
               _loc12_.SetTextPos(-_loc2_.x,_loc2_.y);
            }
            _loc13_ = this["mc_red"];
            _loc14_ = this["mc_blue"];
            if(_loc13_ != null && _loc14_ != null)
            {
               _loc6_ = _loc13_.x;
               _loc13_.x = -_loc14_.x;
               _loc14_.x = -_loc6_;
            }
            _loc15_ = this["mc_base3"];
            if(_loc15_ != null)
            {
               _loc15_.x *= -1;
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
         this.txt_set.SetTextFieldWidth(740);
         this.txt_set.SetTextFit(true);
         this.txt_join.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_join.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_join.SetTextFieldWidth(49);
         this.txt_join.SetTextFit(true);
         this.txt_com.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_com.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_com.SetTextFieldWidth(49);
         this.txt_com.SetTextFit(true);
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
         this.txt_set.SetTextFieldWidth(740);
         this.txt_set.SetTextFit(true);
         this.txt_join.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_join.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_join.SetTextFieldWidth(49);
         this.txt_join.SetTextFit(true);
         this.txt_com.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_com.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_com.SetTextFieldWidth(49);
         this.txt_com.SetTextFit(true);
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
         this.txt_title_set00.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_title_set00.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_title_set00.SetTextFieldWidth(740);
         this.txt_title_set00.SetTextFit(true);
         this.txt_set.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_set.SetTextSize(33);
         this.txt_set.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_set.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_set.SetTextFieldWidth(740);
         this.txt_set.SetTextFit(true);
         this.txt_join.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_join.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_join.SetTextFieldWidth(49);
         this.txt_join.SetTextFit(true);
         this.txt_com.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_com.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_com.SetTextFieldWidth(49);
         this.txt_com.SetTextFit(true);
         this.mc_base2.alpha = 0;
      }
      
      internal function frame4() : *
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
         this.txt_set.SetTextFieldWidth(740);
         this.txt_set.SetTextFit(true);
         this.txt_join.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_join.SetTextColor(5592405);
         this.txt_join.SetTextFieldWidth(49);
         this.txt_join.SetTextFit(true);
         this.txt_com.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_com.SetTextColor(5592405);
         this.txt_com.SetTextFieldWidth(49);
         this.txt_com.SetTextFit(true);
         this.mc_base2.alpha = 0;
      }
   }
}

