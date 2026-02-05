import React from 'react';
import { Check, X } from 'lucide-react';

interface PasswordStrengthProps {
  password: string;
}

const PasswordStrength: React.FC<PasswordStrengthProps> = ({ password }) => {
  const requirements = [
    {
      text: 'At least 8 characters',
      test: (pwd: string) => pwd.length >= 8,
    },
    {
      text: 'One uppercase letter',
      test: (pwd: string) => /[A-Z]/.test(pwd),
    },
    {
      text: 'One lowercase letter',
      test: (pwd: string) => /[a-z]/.test(pwd),
    },
    {
      text: 'One number',
      test: (pwd: string) => /\d/.test(pwd),
    },
    {
      text: 'One special character',
      test: (pwd: string) => /[@$!%*?&]/.test(pwd),
    },
  ];

  const metRequirements = requirements.filter(req => req.test(password));
  const strengthPercentage = (metRequirements.length / requirements.length) * 100;
  
  const getStrengthColor = () => {
    if (strengthPercentage < 40) return 'bg-red-500';
    if (strengthPercentage < 80) return 'bg-yellow-500';
    return 'bg-green-500';
  };

  const getStrengthText = () => {
    if (strengthPercentage < 40) return 'Weak';
    if (strengthPercentage < 80) return 'Good';
    return 'Strong';
  };

  return (
    <div className="mt-3 p-4 bg-slate-800/30 rounded-lg border border-slate-700">
      <div className="flex items-center justify-between mb-3">
        <span className="text-sm font-medium text-slate-300">Password Strength</span>
        <span className={`text-sm font-medium ${
          strengthPercentage < 40 ? 'text-red-400' :
          strengthPercentage < 80 ? 'text-yellow-400' : 'text-green-400'
        }`}>
          {getStrengthText()}
        </span>
      </div>
      
      {/* Progress Bar */}
      <div className="w-full bg-slate-700 rounded-full h-2 mb-4">
        <div
          className={`h-2 rounded-full transition-all duration-300 ${getStrengthColor()}`}
          style={{ width: `${strengthPercentage}%` }}
        />
      </div>

      {/* Requirements List */}
      <div className="space-y-2">
        {requirements.map((requirement, index) => {
          const isMet = requirement.test(password);
          return (
            <div key={index} className="flex items-center text-sm">
              <div className={`w-4 h-4 rounded-full flex items-center justify-center mr-3 transition-colors ${
                isMet ? 'bg-green-500' : 'bg-slate-600'
              }`}>
                {isMet ? (
                  <Check className="w-2.5 h-2.5 text-white" />
                ) : (
                  <X className="w-2.5 h-2.5 text-slate-400" />
                )}
              </div>
              <span className={isMet ? 'text-green-400' : 'text-slate-400'}>
                {requirement.text}
              </span>
            </div>
          );
        })}
      </div>
    </div>
  );
};

export default PasswordStrength;