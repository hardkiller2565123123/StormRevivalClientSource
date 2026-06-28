package Select
{
   import InputPad.InputPadKeyCode;
   
   public class UiSelect
   {
      
      public static const CCD_LOOP_TYPE_DISABLE:* = 0;
      
      public static const CCD_LOOP_TYPE_ENABLE:* = 1;
      
      public static const CCD_LOOP_TYPE_PUSH:* = 2;
      
      private var m_selVal:int = 0;
      
      private var m_minVal:int = 0;
      
      private var m_maxVal:int = 0;
      
      private var m_decKeyBtn:uint = 0;
      
      private var m_incKeyBtn:uint = 0;
      
      private var m_loopType:int = 0;
      
      private var m_isDispSel:Boolean = false;
      
      private var m_dispSel:int = 0;
      
      private var m_dispNo:int = 0;
      
      private var m_dispNum:uint = 0;
      
      private var m_decSkipKeyBtn:uint = 0;
      
      private var m_incSkipKeyBtn:uint = 0;
      
      private var m_isLineSel:Boolean = false;
      
      private var m_rowVal:int = 0;
      
      private var m_colVal:int = 0;
      
      private var m_rowNum:int = 0;
      
      private var m_colNum:int = 0;
      
      private var m_decLineKeyBtn:uint = 0;
      
      private var m_incLineKeyBtn:uint = 0;
      
      private var m_currDispNum:uint = 0;
      
      private var m_input:InputPadKeyCode = new InputPadKeyCode();
      
      public function UiSelect()
      {
         super();
      }
      
      private static function IsLoopMenu(param1:int, param2:uint, param3:uint) : Boolean
      {
         var _loc4_:Boolean = false;
         switch(param1)
         {
            case CCD_LOOP_TYPE_PUSH:
               if(param2 & param3)
               {
                  _loc4_ = true;
               }
               break;
            case CCD_LOOP_TYPE_ENABLE:
               _loc4_ = true;
               break;
            case CCD_LOOP_TYPE_DISABLE:
            default:
               _loc4_ = false;
         }
         return _loc4_;
      }
      
      public function InitSelect(param1:int, param2:int, param3:int, param4:uint, param5:uint, param6:int) : *
      {
         this.m_selVal = param1;
         this.m_minVal = param2;
         this.m_maxVal = param3;
         this.m_decKeyBtn = param4;
         this.m_incKeyBtn = param5;
         this.m_loopType = param6;
         this.m_isDispSel = false;
      }
      
      public function InitDispSelect(param1:uint, param2:int, param3:int, param4:int, param5:int, param6:uint, param7:uint, param8:uint, param9:uint, param10:int) : *
      {
         this.m_isDispSel = true;
         this.m_dispNum = param1;
         this.m_currDispNum = param1;
         this.m_dispNo = param2;
         this.m_dispSel = param3;
         this.m_selVal = param2 + param3;
         this.m_minVal = param4;
         this.m_maxVal = param5;
         this.m_decKeyBtn = param6;
         this.m_incKeyBtn = param7;
         this.m_decSkipKeyBtn = param8;
         this.m_incSkipKeyBtn = param9;
         if(param3 < 0 || param3 > this.m_dispNum)
         {
            this.m_dispSel = 0;
            this.m_selVal = this.m_dispNo;
         }
         if(this.m_dispNo < this.m_minVal || this.m_dispNo > this.m_maxVal)
         {
            this.m_dispNo = 0;
            this.m_dispSel = this.m_dispNo;
            this.m_selVal = 0;
         }
         this.m_loopType = param10;
      }
      
      public function InitLineSelect(param1:uint, param2:uint, param3:int, param4:int, param5:int, param6:int, param7:uint, param8:uint, param9:uint, param10:uint, param11:uint, param12:uint) : *
      {
         this.m_isDispSel = true;
         this.m_isLineSel = true;
         this.m_dispNum = param1 * param2;
         this.m_dispNo = param3;
         this.m_dispSel = param4;
         this.m_minVal = param5;
         this.m_maxVal = param6;
         this.m_decKeyBtn = param7;
         this.m_incKeyBtn = param8;
         this.m_decSkipKeyBtn = param11;
         this.m_incSkipKeyBtn = param12;
         this.m_rowNum = param1;
         this.m_colNum = param2;
         this.m_decLineKeyBtn = param9;
         this.m_incLineKeyBtn = param10;
         this.m_currDispNum = this.m_dispNum;
         if(param4 < 0 || param4 > this.m_dispNum)
         {
            this.m_dispSel = 0;
            this.m_dispNo = 0;
         }
         var _loc13_:int = (int(this.m_maxVal / this.m_colNum) - (this.m_rowNum - 1)) * this.m_colNum;
         if(_loc13_ < 0)
         {
            _loc13_ = 0;
         }
         var _loc14_:int = this.m_dispNo % this.m_colNum;
         if(this.m_dispNo < this.m_minVal || this.m_dispNo > this.m_maxVal)
         {
            this.m_dispNo = 0;
            this.m_dispSel = this.m_dispNo;
         }
         else if(this.m_dispNo >= _loc13_)
         {
            this.m_dispNo = _loc13_;
            this.m_currDispNum = this.m_maxVal - _loc13_;
         }
         else if(_loc14_)
         {
            this.m_dispNo -= _loc14_;
         }
         this.m_selVal = this.m_dispNo + this.m_dispSel;
         this.m_rowVal = int(this.m_dispSel / this.m_colNum);
         this.m_colVal = this.m_dispSel % this.m_colNum;
         this.m_loopType = CCD_LOOP_TYPE_PUSH;
         trace("highestDispNo : " + _loc13_);
      }
      
      public function SelectMenuCtrl() : int
      {
         var _loc1_:uint = this.m_input.GetPadPress();
         var _loc2_:uint = this.m_input.GetPadRepeat();
         if(this.m_isDispSel == true)
         {
            if(this.m_isLineSel == true)
            {
               this.m_selVal = this.LineSelectMenuCtrlCore(_loc1_,_loc2_);
            }
            else
            {
               this.m_selVal = this.DispSelectMenuCtrlCore(_loc1_,_loc2_);
            }
         }
         else
         {
            this.m_selVal = this.SelectMenuCtrlCore(_loc1_,_loc2_);
         }
         return this.m_selVal;
      }
      
      public function IsDispSelect() : Boolean
      {
         return this.m_isDispSel;
      }
      
      public function GetSelValue() : int
      {
         return this.m_selVal;
      }
      
      public function GetDispSelValue() : int
      {
         var _loc1_:int = this.m_dispSel;
         if(this.m_isDispSel == false)
         {
            _loc1_ = -1;
         }
         return _loc1_;
      }
      
      public function GetDispNo() : int
      {
         var _loc1_:int = this.m_dispNo;
         if(this.m_isDispSel == false)
         {
            _loc1_ = 0;
         }
         return _loc1_;
      }
      
      public function GetDispNum() : int
      {
         var _loc1_:int = int(this.m_currDispNum);
         if(this.m_isDispSel == false)
         {
            _loc1_ = this.m_maxVal;
         }
         return _loc1_;
      }
      
      public function SIDE_1P() : uint
      {
         return this.m_input.GetPad_1P();
      }
      
      public function SIDE_2P() : uint
      {
         return this.m_input.GetPad_2P();
      }
      
      public function SetSelValue(param1:int) : *
      {
         if(param1 >= this.m_minVal && param1 <= this.m_maxVal)
         {
            this.m_selVal = param1;
         }
      }
      
      public function SetMinValue(param1:int) : *
      {
         this.m_minVal = param1;
      }
      
      public function SetMaxValue(param1:int) : *
      {
         this.m_maxVal = param1;
      }
      
      public function SetDecKeyBtn(param1:uint) : *
      {
         this.m_decKeyBtn = param1;
      }
      
      public function SetIncKeyBtn(param1:uint) : *
      {
         this.m_incKeyBtn = param1;
      }
      
      public function SetLoopType(param1:int) : *
      {
         this.m_loopType = param1;
      }
      
      public function SetDispNum(param1:uint) : *
      {
         if(param1 <= this.m_maxVal)
         {
            this.m_dispNum = param1;
         }
      }
      
      public function SetDispNo(param1:int) : *
      {
         if(param1 >= this.m_minVal && param1 <= this.m_maxVal)
         {
            this.m_dispNo = param1;
            this.m_selVal = param1 + this.m_dispSel;
         }
      }
      
      public function SetDispSelVal(param1:int) : *
      {
         if(param1 >= 0 && param1 <= this.m_dispNum)
         {
            this.m_dispSel = param1;
         }
      }
      
      public function SetDecSkipKeyBtn(param1:uint) : *
      {
         this.m_decSkipKeyBtn = param1;
      }
      
      public function SetIncSkipKeyBtn(param1:uint) : *
      {
         this.m_incSkipKeyBtn = param1;
      }
      
      public function SetEnablePad(param1:uint) : *
      {
         this.m_input.SetEnablePad(param1);
      }
      
      public function SetDisablePad(param1:uint) : *
      {
         this.m_input.SetDisablePad(param1);
      }
      
      public function EnableAllPad() : *
      {
         this.m_input.EnableAllPad();
      }
      
      public function DisableAllPad() : *
      {
         this.m_input.DisableAllPad();
      }
      
      public function SetEnablePadOnly(param1:uint) : *
      {
         this.m_input.SetEnablePadOnly(param1);
      }
      
      public function SetEnableLocal(param1:Boolean) : *
      {
         this.m_input.SetEnableLocal(param1);
      }
      
      private function SelectMenuCtrlCore(param1:uint, param2:uint) : int
      {
         if(Boolean(param1 & this.m_decKeyBtn) || Boolean(param2 & this.m_decKeyBtn))
         {
            --this.m_selVal;
            if(this.m_selVal < this.m_minVal)
            {
               if(IsLoopMenu(this.m_loopType,param1,this.m_decKeyBtn) == true)
               {
                  this.m_selVal = this.m_maxVal;
               }
               else
               {
                  this.m_selVal = this.m_minVal;
               }
            }
         }
         else if(Boolean(param1 & this.m_incKeyBtn) || Boolean(param2 & this.m_incKeyBtn))
         {
            ++this.m_selVal;
            if(this.m_selVal > this.m_maxVal)
            {
               if(IsLoopMenu(this.m_loopType,param1,this.m_incKeyBtn) == true)
               {
                  this.m_selVal = this.m_minVal;
               }
               else
               {
                  this.m_selVal = this.m_maxVal;
               }
            }
         }
         return this.m_selVal;
      }
      
      private function DispSelectMenuCtrlCore(param1:uint, param2:uint) : int
      {
         if(param2 & this.m_decKeyBtn)
         {
            --this.m_selVal;
            --this.m_dispSel;
            if(this.m_dispSel < 0)
            {
               --this.m_dispNo;
               this.m_dispSel = 0;
            }
            if(this.m_selVal < this.m_minVal)
            {
               if(IsLoopMenu(this.m_loopType,param1,this.m_decKeyBtn) == true)
               {
                  this.m_selVal = this.m_maxVal;
                  this.m_dispSel = this.m_dispNum - 1;
                  this.m_dispNo = this.m_maxVal - this.m_dispNum + 1;
               }
               else
               {
                  this.m_selVal = this.m_minVal;
                  this.m_dispSel = 0;
                  this.m_dispNo = 0;
               }
            }
         }
         else if(param2 & this.m_incKeyBtn)
         {
            ++this.m_selVal;
            ++this.m_dispSel;
            if(this.m_dispSel >= this.m_dispNum)
            {
               ++this.m_dispNo;
               this.m_dispSel = this.m_dispNum - 1;
            }
            if(this.m_selVal > this.m_maxVal)
            {
               if(IsLoopMenu(this.m_loopType,param1,this.m_incKeyBtn) == true)
               {
                  this.m_selVal = this.m_minVal;
                  this.m_dispSel = 0;
                  this.m_dispNo = 0;
               }
               else
               {
                  this.m_selVal = this.m_maxVal;
                  this.m_dispSel = this.m_dispNum - 1;
                  this.m_dispNo = this.m_maxVal - this.m_dispNum + 1;
               }
            }
         }
         if(param2 & this.m_decSkipKeyBtn)
         {
            this.m_dispNo -= this.m_dispNum;
            if(this.m_dispNo < this.m_minVal)
            {
               this.m_selVal = this.m_minVal;
               this.m_dispSel = 0;
               this.m_dispNo = 0;
            }
            else
            {
               this.m_selVal -= this.m_dispNum;
            }
         }
         else if(param2 & this.m_incSkipKeyBtn)
         {
            this.m_dispNo += this.m_dispNum;
            if(this.m_dispNo + this.m_dispNum - 1 > this.m_maxVal)
            {
               this.m_selVal = this.m_maxVal;
               this.m_dispSel = this.m_dispNum - 1;
               this.m_dispNo = this.m_maxVal - this.m_dispNum + 1;
            }
            else
            {
               this.m_selVal += this.m_dispNum;
            }
         }
         return this.m_selVal;
      }
      
      private function LineSelectMenuCtrlCore(param1:uint, param2:uint) : int
      {
         var _loc3_:int = (int(this.m_maxVal / this.m_colNum) - (this.m_rowNum - 1)) * this.m_colNum;
         if(_loc3_ < 0)
         {
            _loc3_ = 0;
         }
         if(param2 & this.m_decKeyBtn)
         {
            --this.m_selVal;
            --this.m_colVal;
            if(this.m_colVal < 0)
            {
               this.m_colVal += this.m_colNum;
               if(this.m_rowVal == 0)
               {
                  this.m_dispNo -= this.m_colNum;
               }
               else
               {
                  --this.m_rowVal;
               }
            }
            if(this.m_selVal < this.m_minVal)
            {
               if(IsLoopMenu(this.m_loopType,param1,this.m_decKeyBtn) == true)
               {
                  this.m_selVal = this.m_maxVal;
                  this.m_dispNo = _loc3_;
                  this.m_colVal = int((this.m_selVal - this.m_dispNo) % this.m_colNum);
                  this.m_rowVal = this.m_rowNum - 1;
               }
               else
               {
                  this.m_selVal = this.m_minVal;
                  this.m_dispNo = 0;
                  this.m_colVal = 0;
               }
            }
         }
         else if(param2 & this.m_incKeyBtn)
         {
            ++this.m_selVal;
            ++this.m_colVal;
            if(this.m_colVal >= this.m_colNum)
            {
               this.m_colVal -= this.m_colNum;
               if(this.m_rowVal == this.m_rowNum - 1)
               {
                  this.m_dispNo += this.m_colNum;
               }
               else
               {
                  ++this.m_rowVal;
               }
            }
            if(this.m_selVal > this.m_maxVal)
            {
               if(IsLoopMenu(this.m_loopType,param1,this.m_incKeyBtn) == true)
               {
                  this.m_selVal = this.m_minVal;
                  this.m_dispNo = 0;
                  this.m_colVal = 0;
                  this.m_rowVal = 0;
               }
               else
               {
                  this.m_selVal = this.m_maxVal;
                  this.m_dispNo = _loc3_;
                  this.m_colVal = int((this.m_selVal - this.m_dispNo) % this.m_colNum);
               }
            }
         }
         if(param2 & this.m_decSkipKeyBtn)
         {
            if(this.m_dispNo != 0)
            {
               this.m_dispNo -= this.m_colNum * this.m_rowNum;
            }
            else if(this.m_rowVal == 0)
            {
               this.m_dispNo -= this.m_colNum * this.m_rowNum;
            }
            else
            {
               this.m_rowVal = 0;
            }
            if(this.m_dispNo < 0)
            {
               if(IsLoopMenu(this.m_loopType,param1,this.m_decSkipKeyBtn) == true)
               {
                  if(this.m_dispNo <= -(this.m_rowNum * this.m_colNum))
                  {
                     this.m_dispNo = _loc3_;
                     this.m_rowVal = this.m_rowNum - 1;
                  }
                  else
                  {
                     this.m_dispNo = 0;
                  }
                  this.m_selVal = this.m_dispNo + this.m_rowVal * this.m_colNum + this.m_colVal;
                  if(this.m_maxVal < this.m_selVal)
                  {
                     this.m_colVal -= this.m_selVal - this.m_maxVal;
                  }
               }
               else
               {
                  this.m_dispNo = 0;
               }
            }
            this.m_selVal = this.m_dispNo + this.m_rowVal * this.m_colNum + this.m_colVal;
         }
         else if(param2 & this.m_incSkipKeyBtn)
         {
            if(this.m_dispNo != _loc3_)
            {
               this.m_dispNo += this.m_colNum * this.m_rowNum;
            }
            else if(this.m_rowVal == this.m_rowNum - 1)
            {
               this.m_dispNo += this.m_colNum * this.m_rowNum;
            }
            else
            {
               this.m_rowVal = this.m_rowNum - 1;
               if(this.m_maxVal < _loc3_ + this.m_rowVal * this.m_colNum + this.m_colVal)
               {
                  this.m_colVal = this.m_maxVal % this.m_colNum;
               }
            }
            if(this.m_dispNo > _loc3_)
            {
               if(IsLoopMenu(this.m_loopType,param1,this.m_incSkipKeyBtn) == true)
               {
                  if(this.m_dispNo - _loc3_ < this.m_rowNum * this.m_colNum)
                  {
                     this.m_dispNo = _loc3_;
                  }
                  else
                  {
                     this.m_dispNo = 0;
                     this.m_selVal = this.m_minVal + this.m_colVal;
                     this.m_rowVal = 0;
                  }
               }
               else
               {
                  this.m_dispNo = _loc3_;
               }
            }
            this.m_selVal = this.m_dispNo + this.m_rowVal * this.m_colNum + this.m_colVal;
         }
         if(param2 & this.m_decLineKeyBtn)
         {
            if(this.m_rowVal != 0)
            {
               --this.m_rowVal;
            }
            else
            {
               this.m_dispNo -= this.m_colNum;
            }
            if(this.m_dispNo < 0)
            {
               if(IsLoopMenu(this.m_loopType,param1,this.m_decLineKeyBtn) == true)
               {
                  this.m_dispNo = _loc3_;
                  this.m_rowVal = this.m_rowNum - 1;
                  this.m_selVal = this.m_dispNo + this.m_rowVal * this.m_colNum + this.m_colVal;
                  if(this.m_maxVal < this.m_selVal)
                  {
                     this.m_colVal -= this.m_selVal - this.m_maxVal;
                  }
               }
               else
               {
                  this.m_dispNo = 0;
               }
            }
            this.m_selVal = this.m_dispNo + this.m_rowVal * this.m_colNum + this.m_colVal;
         }
         else if(param2 & this.m_incLineKeyBtn)
         {
            if(this.m_rowVal < this.m_rowNum - 1)
            {
               ++this.m_rowVal;
               if(this.m_maxVal < this.m_dispNo + this.m_rowVal * this.m_colNum + this.m_colVal)
               {
                  this.m_colVal = this.m_maxVal % this.m_colNum;
               }
            }
            else
            {
               if(this.m_maxVal < this.m_dispNo + this.m_rowVal * this.m_colNum + this.m_colVal)
               {
                  this.m_colVal = this.m_maxVal % this.m_colNum;
               }
               this.m_dispNo += this.m_colNum;
            }
            if(this.m_dispNo > _loc3_)
            {
               if(IsLoopMenu(this.m_loopType,param1,this.m_incLineKeyBtn) == true)
               {
                  this.m_selVal = this.m_minVal + this.m_colVal;
                  this.m_dispNo = 0;
                  this.m_rowVal = 0;
               }
               else
               {
                  this.m_dispNo = _loc3_;
               }
            }
            this.m_selVal = this.m_dispNo + this.m_rowVal * this.m_colNum + this.m_colVal;
         }
         this.m_dispSel = this.m_selVal - this.m_dispNo;
         if(this.m_dispNo == _loc3_)
         {
            this.m_currDispNum = this.m_maxVal - _loc3_;
         }
         else
         {
            this.m_currDispNum = this.m_colNum * this.m_rowNum;
         }
         return this.m_selVal;
      }
   }
}

