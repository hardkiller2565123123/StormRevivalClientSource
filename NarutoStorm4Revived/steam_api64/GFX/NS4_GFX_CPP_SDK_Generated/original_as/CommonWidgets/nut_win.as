package script.option_win
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol457")]
   public class nut_win extends MovieClip
   {
      
      private static const ITEM_NUM:* = 2;
      
      private static const CCD_WINDOW_BLANK_Y:* = 18;
      
      private static const CCD_WINDOW_INS_BLANK_Y:* = 32;
      
      private static const CCD_WINDOW_MARGIN_X:* = 100;
      
      private static const CCD_WINDOW_MARGIN_Y:* = CCD_WINDOW_BLANK_Y + CCD_WINDOW_INS_BLANK_Y;
      
      private static const CCD_CURSOR_MARGIN_X:* = 28;
      
      public var mc_bar1:MovieClip;
      
      public var mc_bar2:MovieClip;
      
      public var mc_msg1:MovieClip;
      
      public var mc_msg2:MovieClip;
      
      public var mc_win:anm_win00;
      
      private var m_selectBar:Array = new Array();
      
      private var m_callbackFunction:Function;
      
      public function nut_win()
      {
         super();
         addFrameScript(3,this.frame4,7,this.frame8);
      }
      
      public function Initialize(param1:Number, param2:Number) : *
      {
         var _loc3_:Array = null;
         var _loc4_:Array = null;
         var _loc5_:Array = null;
         var _loc14_:MovieClip = null;
         var _loc15_:MovieClip = null;
         var _loc16_:MovieClip = null;
         _loc3_ = ["eng","fre","spa","ger","ita","rus","pol","arae","thth"];
         _loc4_ = [_loc3_[param1] + "_" + _loc3_[param2],_loc3_[param2] + "_" + _loc3_[param2]];
         _loc5_ = ["yes","no"];
         var _loc6_:int = 0;
         var _loc7_:int = 0;
         var _loc8_:int = 0;
         var _loc9_:int = 0;
         var _loc10_:int = 0;
         while(_loc10_ < ITEM_NUM)
         {
            _loc14_ = this["mc_bar" + (_loc10_ + 1)];
            if(_loc14_ == null)
            {
               trace("failed: " + "mc_bar" + (_loc10_ + 1));
               return;
            }
            _loc14_.gotoAndStop(_loc5_[_loc10_]);
            _loc15_ = _loc14_["mc_" + _loc5_[_loc10_]];
            if(_loc15_ == null)
            {
               trace("failed: " + "mc_" + _loc5_[_loc10_]);
               return;
            }
            _loc15_.gotoAndStop(_loc5_[_loc10_] + "_" + _loc4_[0]);
            if(_loc15_.width > _loc6_)
            {
               _loc6_ = _loc15_.width;
            }
            this.m_selectBar.push(_loc14_["mc_base"]);
            if(this.m_selectBar[_loc10_] == null)
            {
               trace("failed: mc_base");
               return;
            }
            if(_loc10_ >= ITEM_NUM - 1)
            {
               _loc9_ = _loc14_.y + _loc14_.height / 2;
            }
            _loc16_ = this["mc_msg" + (_loc10_ + 1)];
            if(_loc16_ == null)
            {
               trace("failed: " + "mc_msg" + (_loc10_ + 1));
               return;
            }
            _loc16_.gotoAndStop("ctn_" + _loc4_[_loc10_]);
            if(_loc16_.width > _loc7_)
            {
               _loc7_ = _loc16_.width;
            }
            if(_loc10_ <= 0)
            {
               _loc8_ = _loc16_.y - _loc16_.height / 2;
            }
            _loc10_++;
         }
         var _loc11_:int = 0;
         while(_loc11_ < this.m_selectBar.length)
         {
            if(this.m_selectBar[_loc11_] == null)
            {
               trace("failed: " + _loc11_);
               return;
            }
            this.m_selectBar[_loc11_].width = _loc6_ + CCD_CURSOR_MARGIN_X * 2;
            _loc11_++;
         }
         this.SetSelect(true);
         var _loc12_:int = _loc7_;
         if(this.m_selectBar[0].width > _loc12_)
         {
            _loc12_ = int(this.m_selectBar[0].width);
         }
         var _loc13_:MovieClip = this["mc_win"];
         if(_loc13_ == null)
         {
            trace("failed: mc_win");
            return;
         }
         _loc13_.mc_win00.width = _loc12_ + CCD_WINDOW_MARGIN_X * 2;
         _loc13_.mc_win00.height = _loc9_ - _loc8_ + CCD_WINDOW_MARGIN_Y * 2;
      }
      
      public function SetSelect(param1:Boolean) : *
      {
         this.m_selectBar[0].visible = param1;
         this.m_selectBar[1].visible = !param1;
      }
      
      public function SetCallbackFunction(param1:Function) : *
      {
         this.m_callbackFunction = param1;
      }
      
      private function Callback() : *
      {
         this.m_callbackFunction();
      }
      
      public function SetVisible(param1:Boolean) : *
      {
         var _loc2_:int = 0;
         while(_loc2_ < ITEM_NUM)
         {
            this["mc_msg" + (_loc2_ + 1)].visible = param1;
            this["mc_bar" + (_loc2_ + 1)].visible = param1;
            _loc2_++;
         }
      }
      
      internal function frame4() : *
      {
         stop();
         this.Callback();
      }
      
      internal function frame8() : *
      {
         this.stop();
         this.Callback();
      }
   }
}

